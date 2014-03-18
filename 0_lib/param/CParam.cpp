///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CParam.cpp,v $
// $Revision: 1.5 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "CParam.h"


///////////////////////////////////////////////////////////////////////////////
// scale given value

static float scale(float inval, float inmin, float inmax, float retmin, float retmax )
{
	if(inmin!=retmin || inmax!=retmax)
	{
		float bpsrc = 0., bpdst = 0.;
		
		if( inmax>inmin && inmin<0 && inmax>0 )
		{
			bpsrc = (inval >= 0) ? inmax : inmin;
		}
		else if( inmin>inmax && inmax<0 && inmin>0 )
		{
			bpsrc = (inval < 0) ? inmax : inmin;
		}
		
		if( retmax>retmin && retmin<0 && retmax>0 )
		{
			bpdst = (inval >= 0) ? retmax : retmin;
		}
		else if( retmin>retmax && retmax<0 && retmin>0 )
		{
			bpdst = (inval < 0) ? retmax : retmin;
		}
		
		if(bpsrc&&bpdst)
		{
			inval /= bpsrc;
			inval *= bpdst;
		}
		else if(inmin != inmax)
		{
			inval -= inmin;
			inval /= inmax - inmin;
			inval *= retmax - retmin;
			inval += retmin;
		}
		else
		{
			inval = retmin;
		}
	}
	return inval;
}


///////////////////////////////////////////////////////////////////////////////
// CParam methods

///////////////////////////////////////////////////////////////////////////////
// constructor notifyer

CParam::td_notify::td_notify(void)
{
	clear();
}

void CParam::td_notify::clear(void)
{
	min = 0.;
	max = 0.;
	inf[0] = 0;
	inf[1] = 0;
	PreCbFn = 0;
	PstCbFn = 0;
}

///////////////////////////////////////////////////////////////////////////////
// constructor

CParam::CParam()
{
	mDscr1=mDscr2=mName = "";
	mMin = 0.;
	mMax = 0.;
	mDef = 0.;
	mQuant = 1.;
	mVal = 0.;
	
	mNumNotifyers = 16;
	mNotify = new CParam::td_notify *[mNumNotifyers];
	for(int i=0; i<mNumNotifyers; i++) mNotify[i] = 0;
}


///////////////////////////////////////////////////////////////////////////////
// destructor

CParam::~CParam()
{
	// frees freed resources ?
	//  for(int i=0; i<mNumNotifyers; i++) if(mNotify[i]) delete mNotify[i];
}


///////////////////////////////////////////////////////////////////////////////
// add notifyer

bool CParam::AddNotify( td_notify *notify, bool defminmax, short flags )
{
	int i;
	
	for(i=0; i<mNumNotifyers; i++)
	{
		if(!mNotify[i]) break;
	}
	if(i>=mNumNotifyers) return false;
	
	mNotify[i] = notify;
	
	// and notify then
	if(defminmax)
	{
		notify->min = mMin;
		notify->max = mMax;
	}
	float ntfvals[2] = {mVal,mVal};
	NotifyVal(true, ntfvals, flags|NFLG_FORCE, notify);
    
#ifdef DBG_SHOW
	showlist((td_ntflist *)mNtfList);
#endif
	
	return true;
}


///////////////////////////////////////////////////////////////////////////////
// remove notifyer

void CParam::RmvNotify( td_notify *notify )
{
	int i;
	
	for(i=0; i<mNumNotifyers; i++)
	{
		if(mNotify[i] == notify) break; //found
	}
	if(i>=mNumNotifyers) return;  //not found
	
	for(i++;i<mNumNotifyers;i++)
	{
		mNotify[i-1] = mNotify[i];
		if(!mNotify[i]) break;
	}
	mNotify[mNumNotifyers-1] = 0;
	
	
#ifdef DBG_SHOW
	showlist((td_ntflist *)mNtfList);
#endif
}


///////////////////////////////////////////////////////////////////////////////
// set the value of a given index and call valfn according to mode
// return true if the value has changed

bool CParam::SetVal( float val, short flags, td_notify *notify )
{
	//printf("CParam::SetVal(%f, %04X, %06lX)\n", inVal, inFlags, (long)inNotify);
	if( notify && notify->min != notify->max )
	{
		val = scale(val, notify->min,notify->max, mMin,mMax);
	}
	//printf("CParam::SetVal(%f, %04X, %06lX) scaled\n", inVal, inFlags, (long)inNotify);
	
	if( mQuant )
	{
		// quantize value
		int tmp = (int)(val/mQuant);
		val =  (float)(tmp);
		val *= mQuant;
	}
	//printf("CParam::SetVal(%f, %04X, %06lX) quantized\n", inVal, inFlags, (long)inNotify);
	
	// clip or crop inval into borders
	if(flags & NFLG_CLIP)
	{
		val = (val < mMin) ? mMax : (val > mMax) ? mMin : val;
	}
	else
	{
		val = (val < mMin) ? mMin : (val > mMax) ? mMax : val;
	}
	
	// call pre notify-fn
	float ntfvals[2] = {mVal,val};
	if( NotifyVal(false, ntfvals, flags, notify) )
	{
		mVal = val;
	}
	else
	{
		ntfvals[1] = mVal;
	}
	
	// call post notify-fn
	NotifyVal(true, ntfvals, flags, notify);
	
	return ( ntfvals[0] != ntfvals[1] );
}


///////////////////////////////////////////////////////////////////////////////
// reset mVal to default

bool CParam::ResetVal( short flags )
{
	return SetVal(mDef,flags);
}


///////////////////////////////////////////////////////////////////////////////
// step val for given amount

bool CParam::StepVal( int step, short flags, td_notify *notify )
{
	return SetVal( (float)step*mQuant + mVal, flags, notify);
}


///////////////////////////////////////////////////////////////////////////////
// return the value of a given index

float CParam::GetVal( td_notify *notify )
{
	float r=mVal = (mVal < mMin) ? mMin : (mVal > mMax) ? mMax : mVal;
	
	if( notify )
	{
		if( mMax != mMin )
		{
			r = scale(r, mMin,mMax, notify->min,notify->max );
		}
		else
		{
			r = notify->min;
		}
	}
	
	return r;
}


///////////////////////////////////////////////////////////////////////////////
// call notify-fns of the values

bool CParam::NotifyVal( bool post, float *inval, short flags, td_notify *notify )
{
	bool confirm = true;
	bool diffrnt = inval[0]!=inval[1];
	int i;
	
	if(flags)
	{
		float val[2];
		
		for(i=0; i<mNumNotifyers; i++)
		{
			if(mNotify[i] == 0) break;
			
			if( mNotify[i] == notify )
			{
				if( (flags & NFLG_SELF) == 0 ) continue;
			}
			else
			{
				if( (flags & NFLG_OTHERS) == 0 ) continue;
			}
			
			if(post)
			{
				if(mNotify[i]->PstCbFn && ( diffrnt || (flags & NFLG_FORCE) ))
				{
					val[0] = scale(inval[0], mMin,mMax, mNotify[i]->min,mNotify[i]->max );
					val[1] = scale(inval[1], mMin,mMax, mNotify[i]->min,mNotify[i]->max );
					mNotify[i]->PstCbFn(val,this,mNotify[i]->inf);
				}
			}
			else
			{
				if(mNotify[i]->PreCbFn && ( diffrnt || (flags & NFLG_FORCE) ))
				{
					val[0] = scale(inval[0], mMin,mMax, mNotify[i]->min,mNotify[i]->max );
					val[1] = scale(inval[1], mMin,mMax, mNotify[i]->min,mNotify[i]->max );
					if(mNotify[i]->PreCbFn(val,this,mNotify[i]->inf) == false)
					{
						confirm = false;
					}
				}
			}
		}
	}
	
	return confirm;
}


///////////////////////////////////////////////////////////////////////////////
// return whether mVal is bipolar

bool CParam::IsBipolar( void )
{
	return (mMax>mMin && mMin<0 && mMax>0) || (mMin>mMax && mMax<0 && mMin>0);
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CParam.cpp,v $
// Revision 1.5  2004/11/11 03:14:20  joffe
// reset-val added
//
// Revision 1.4  2004/08/26 00:43:38  joffe
// number of notifyers raised from 8 to 16
//
// Revision 1.3  2004/08/24 20:05:34  joffe
// 'i' declaration scope changed due to gcc-warning
//
// Revision 1.2  2004/08/24 19:02:34  joffe
// notify-functions now called in addnotify-order
// notifyers changed from linked list to array
//
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
