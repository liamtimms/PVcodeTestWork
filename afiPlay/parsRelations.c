/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/demo/gre/parsRelations.c,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: parsRelations.c,v 1.3 2013/09/06 12:38:39 sako Exp $
 *
 * ***************************************************************/


static const char resid[] = "$Id: parsRelations.c,v 1.3 2013/09/06 12:38:39 sako Exp $ (c) 2007 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR	0



#include "method.h"

/* =============================================================
 * Default relations and range checking functions of parameters
 * that appear editable in the method editor
 * ============================================================= */

/* ============================================================
 * Globally defined parameters: The relation has been redirected 
 * (see callbackDefs.h)
 * ============================================================ */

/* ------------------------------------------------------------
 * Repetition Time TR (normal commented out)
 * ------------------------------------------------------------ */
/*
void RepetitionTimeRange(void)
{
  
  DB_MSG(("-->RepetitionTimeRange"));

  if(ParxRelsParHasValue("PVM_RepetitionTime")==No)
  {
    PVM_RepetitionTime = 100.0;

  }
  else
  {
    PVM_RepetitionTime = MAX_OF(1e-3,PVM_RepetitionTime);
  }

  
  DB_MSG(("<--RepetitionTimeRange"));
  return;
}

void RepetitionTimeRel(void)
{
  DB_MSG(("-->RepetitionTimeRel"));

  RepetitionTimeRange();
  backbone();

  DB_MSG(("<--RepetitionTimeRel"));
  return;
}
*/

void afi_TR1Range(void)
{
	DB_MSG(("-->afi_TR1Range"));
	
	if(ParxRelsParHasValue("afi_TR1")==No)
	{
		afi_TR1 = 30.0;
	}
	else
	{
		afi_TR1 = MAX_OF(1e-3,afi_TR1);
	}
	
	DB_MSG(("<--afi_TR1Range"));
	return;
}

void afi_TR1Rel(void)
{
	DB_MSG(("-->afi_TR1Rel"));
	
	afi_TR1Range();
	backbone();
	
	DB_MSG(("-->afi_TR1Rel"));
	return;
}

void afi_TR2Range(void)
{
	DB_MSG(("-->afi_TR2Range"));
	
	if(ParxRelsParHasValue("afi_TR2")==No)
	{
		afi_TR2 = 150.0;
	}
	else
	{
		afi_TR2 = MAX_OF(1e-3,afi_TR2); //might want to change this so that the min is TR1
	}
	
	DB_MSG(("<--afi_TR2Range"));
	return;
}

void afi_TR2Rel(void)
{
	DB_MSG(("-->afi_TR2Rel"));
	
	afi_TR2Range();
	backbone();
	
	DB_MSG(("-->afi_TR2Rel"));
	return;
}

void afi_total_TRRange(void)
{
	DB_MSG(("-->afi_total_TRRange"));
	
	if(ParxRelsParHasValue("afi_total_TR")==No)
	{
		afi_total_TR = afi_TR1 + afi_TR2;
	}
	else
	{
		afi_total_TR = MAX_OF(1e-3,afi_total_TR);
	}
	
	DB_MSG(("<--afi_total_TR"));
	return;
}

void afi_total_TRRel(void)
{
	DB_MSG(("-->afi_total_TRRel"));
	
	afi_TR2Range();
	backbone();
	
	DB_MSG(("-->afi_total_TRRel"));
	return;
}

/* -------------------------------------------------------------
 * Averages NA
 * ------------------------------------------------------------*/

void AveragesRange(void)
{
  
  DB_MSG(("-->AveragesRange"));

  if(ParxRelsParHasValue("PVM_NAverages")==No)
  {
    PVM_NAverages = 1;

  }
  else
  {
    PVM_NAverages = MAX_OF(1,PVM_NAverages);
  }

  
  DB_MSG(("<--AveragesRange"));
  return;
}

void AveragesRel(void)
{
  DB_MSG(("-->AveragesRel"));

  AveragesRange();
  backbone();

  DB_MSG(("<--AveragesRel"));
  return;
}

/* ------------------------------------------------------------
 * Echo Time TE
 * -----------------------------------------------------------*/
 
void EchoTimeRange(void)
{
  
  DB_MSG(("-->EchoTimeRange"));

  if(ParxRelsParHasValue("PVM_EchoTime")==No)
  {
    PVM_EchoTime = 6.0;

  }
  else
  {
    PVM_EchoTime = MAX_OF(1e-3,PVM_EchoTime);
  }
  
  DB_MSG(("<--EchoTimeRange"));
  return;
}

void EchoTimeRel(void)
{
  DB_MSG(("-->EchoTimeRel"));

  EchoTimeRange();
  backbone();

  DB_MSG(("<--EchoTimeRel"));
  return;
}


/* -------------------------------------------------------------
 * Bandwidth of data sampling PVM_EffSWh
 * ------------------------------------------------------------*/

void EffSWhRange(void)
{
  DB_MSG(("-->EffSWhRange"));

  if(!ParxRelsParHasValue("PVM_EffSWh"))
  {
    PVM_EffSWh=50000;
  }
  else
  {
    double dval;
    /* constrain */
    dval = PVM_EffSWh;
    PVM_EffSWh=MAX_OF(MIN_OF(1000000.0,dval),2000.0);
  }

  DB_MSG(("<--EffSWhRange"));
}

void EffSWhRel(void)
{
  DB_MSG(("-->EffSWhRel"));

  EffSWhRange();
  backbone();

  DB_MSG(("<--EffSWhRel"));
}


/* =============================================================
 * Locally (i.e. in parsDefinition.h) defined parameters
 * ============================================================= */

/* -------------------------------------------------------------
 * Duration of Encoding Gradient
 * ------------------------------------------------------------- */

void EncGradDurRange(void)
{
  double min;

  DB_MSG(("-->EncGradDurRange"));

  min = 2*CFG_GradientRiseTime() + CFG_InterGradientWaitTime();
  if(!ParxRelsParHasValue("EncGradDur"))
  {
    EncGradDur=MAX_OF(2.0,min);
  }
  else
  {
    EncGradDur=MAX_OF(EncGradDur,min);
  }

  DB_MSG(("<--EncGradDurRange"));

}

void EncGradDurRel(void)
{
  DB_MSG(("-->EncGradDurRel"));

  EncGradDurRange();
  backbone();

  DB_MSG(("<--EncGradDurRel"));
}


/* -----------------------------------------------------------
 * Duration of read spoiling gradient
 * ----------------------------------------------------------*/

void ReadSpoilGradDurRange(void)
{
  double min;

  DB_MSG(("-->ReadSpoilGradDurRange"));
  min = 2.0*CFG_GradientRiseTime() +
    CFG_InterGradientWaitTime();


  if (!ParxRelsParHasValue("ReadSpoilGradDur"))
  {
    ReadSpoilGradDur = MAX_OF(min,1.0);
  }
  else
  {
    ReadSpoilGradDur = 
      MAX_OF(ReadSpoilGradDur,min);
  }

  DB_MSG(("<--ReadSpoilGradDurRange"));
}


void ReadSpoilGradDurRel(void)
{
  DB_MSG(("-->ReadSpoilGradDurRel"));

  ReadSpoilGradDurRange();
  backbone();

  DB_MSG(("<--ReadSpoilGradDurRel"));
}


/* ===================================================================
 * Relation of ExcPulse
 * 
 * All pulses of type PVM_RF_PULSE must have relations like this.
 * However, if you clone this funtion for a different pulse parameter
 * remember to replace the param name in the call to UT_SetRequest!
 *
 * IMPORTANT: this function should not be invoked in the backbone!
 ====================================================================*/

void ExcPulse1Relation(void)
{
  DB_MSG(("-->ExcPulse1Relation"));
  
  /*
   * Tell the request handling system that the parameter
   * ExcPulse has been edited 
   */
  
  UT_SetRequest("ExcPulse1");
  
  /* Check the values of ExcPulse */
  
  ExcPulse1Range();
  
  /* 
   * call the backbone; further handling will take place there
   * (by means of STB_UpdateRFPulse)  
   */
  
  backbone();
  
  DB_MSG(("<--ExcPulse1Relation"));
}



void ExcPulse1Range(void)
{
  DB_MSG(("-->ExcPulse1Range"));
  
  // range checker fields to be controlled may be
  // .Length  
  // .Bandwidth
  // .Flipangle
  // .Calculated
  // .Sharpness
  // .Flatness   
 double dval=ExcPulse1.Flipangle;
  
 ExcPulse1.Flipangle = MIN_OF(90.0,MAX_OF(dval,1.0));

 DB_MSG(("<--ExcPulseRange")); 
}
