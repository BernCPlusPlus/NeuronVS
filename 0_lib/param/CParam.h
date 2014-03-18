///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CParam.h,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// CParam is a 'Parameter' that occupies a float 'Value' and necessary infor-
// mation such as min/max and default-value settings, textual description and
// so on. Furthermore for this 'Value' any number of so called 'Notifyers' can
// be appended, each specifies at least a min/max range, if needed 2 void poin-
// ters and callbacks can also be used. Whenever the 'Value' should be changed,
// all pre-'Notifyers' will be informed, which should return true as confirma-
// tion to change the 'Value', otherwise 'Value' remains. After setting 'Value'
// all post-'Notifyers' will be called. The source of change can be any of the
// 'Notifyers' or the root itself. A choice can be set how 'Notifyers' will be
// callbacked on a change of 'Value'.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CPARAM_H
#define CPARAM_H

// notify flags determine how and whether 'Notifyer' callback is called

#define NFLG_NONE   0  // don't call notify, regardless what happened
#define NFLG_SELF   1  // call only inquiror if 'Value' changed
#define NFLG_OTHERS 2  // call others (not inquiror) if 'Value' changed
#define NFLG_ALL    3  // call all if 'Value' changed
#define NFLG_FORCE  4  // ORable: call notify even if 'Value' didn't change
#define NFLG_CLIP   8  // ORable: use clip instead of saturation if 'Value' is
//         out of min/max range


class CParam
{
public:
	
	// the typedefed 'Notifyer', see above
	struct td_notify
	{
		td_notify(void);
		void clear(void);
		
		float min;    // min allowed value (used for scaling)
		float max;    // max allowed value (used for scaling)
		void  *inf[2];// 2 ptrs to any info, passed to notify-fn,
		// this is called before mVal changes, may avoid the change by ret false
		bool (*PreCbFn)( float *inScaledVals, CParam *inParam, void **inInfos );
		// this is called after mVal changed
		void (*PstCbFn)( float *inScaledVals, CParam *inParam, void **inInfos );
		
	} ;
	
	CParam();
	~CParam();
	
	char const *mName;  // parameter name, maybe add more later
	char const *mDscr1; // general purpose description
	char const *mDscr2; // general purpose description
	float mMin;         // min allowed value
	float mMax;         // max allowed value
	float mDef;         // Default value
	float mQuant;       // quantizestep, must be >0
	
	// this appends a 'Notifyer' to the 'Value', 
	bool  AddNotify( td_notify *in, bool iDefminmax=false, short inFlags = NFLG_SELF|NFLG_FORCE );
	void  RmvNotify( td_notify *in );
	
	float GetVal( td_notify *in = 0 );
	bool  SetVal( float inVal, short inFlags = 0, td_notify *inNotify = 0 );
	bool  ResetVal( short inFlags = 0 );
	bool  StepVal( int inStep, short inFlags = 0, td_notify *inNotify = 0 );
	bool  IsBipolar( void );
	
private:
	float mVal;       // actual value
	
	bool  NotifyVal( bool inPreCall, float *inVals, short inFlags = 0, td_notify *inNotify = 0 );
	CParam::td_notify **mNotify;   // list of notifyer-pointers
	int mNumNotifyers;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CParam.h,v $
// Revision 1.3  2004/11/11 03:14:20  joffe
// reset-val added
//
// Revision 1.2  2004/08/24 19:02:34  joffe
// notify-functions now called in addnotify-order
// notifyers changed from linked list to array
//
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
