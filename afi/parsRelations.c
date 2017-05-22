/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/parsRelations.c,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: parsRelations.c,v 1.6.2.3 2007/10/26 05:56:05 mawi Exp $
 *
 * ***************************************************************/


static const char resid[] = "$Id: parsRelations.c,v 1.6.2.3 2007/10/26 05:56:05 mawi Exp $ (c) 2007 Bruker BioSpin MRI GmbH";

#define DEBUG		    0
#define DB_MODULE	  0
#define DB_LINE_NR	0



#include "method.h"

/* =============================================================
 * Default relations and range checking functions of parameters
 * that appear editable in the method editor
 * ============================================================= */

/* ============================================================
 * Globally defined parameters: The relation has been redirected 
 * (see callbackDefs.h)
 * Some of these parameters appear also editable in other
 * parameter editors (e.g. Scan Editor)
 * ============================================================ */

/* ------------------------------------------------------------
 * AFI: Repetition Time TR1
 * ------------------------------------------------------------ */

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

  DB_MSG(("<--afi_TR1Rel"));
  return;
}

/* ------------------------------------------------------------
 * AFI: Repetition Time TR2
 * ------------------------------------------------------------ */

void afi_TR2Range(void)
{
  
  DB_MSG(("-->afi_TR2Range"));

  if(ParxRelsParHasValue("afi_TR2")==No)
  {
    afi_TR2 = 150.0;

  }
  else
  {
    afi_TR2 = MAX_OF(1e-3,afi_TR2);
  }

  
  DB_MSG(("<--afi_TR2Range"));
  return;
}

void afi_TR2Rel(void)
{
  DB_MSG(("-->afi_TR2Rel"));

  afi_TR2Range();
  backbone();

  DB_MSG(("<--afi_TR2Rel"));
  return;
}

/* ------------------------------------------------------------
 * AFI: Repetition Time Total TR
 * ------------------------------------------------------------ */

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

  
  DB_MSG(("<--afi_total_TRRange"));
  return;
}

void afi_total_TRRel(void)
{
  DB_MSG(("-->afi_total_TRRel"));

  afi_total_TRRange();
  backbone();

  DB_MSG(("<--afi_total_TRRel"));
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
 * Excitation pulse angle (PVM_ExcPulseAngle)
 * this parameter appears editable in the contrast page of the 
 * scan editor and sets directly the flip angle of the 
 * excitation pulse. The range checking  function of the 
 * excitation pulse (see below) assures a legal range. In the 
 * backbone after an update of the RF pulse, the final value of 
 * the flip angle is stored back to PVM_ExcPulseAngle 
 * ------------------------------------------------------------*/

void ExcPulseAngleRelation(void)
{
  DB_MSG(("-->ExcPulseAngleRelation"));

  ExcPulse.FlipAngle = PVM_ExcPulseAngle;
  ExcPulseRange();
  backbone();

  DB_MSG(("<--ExcPulseAngleRelation"));
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
 * Position of the echo inside the acquisition interval
 * ----------------------------------------------------------*/


void EchoPositionRange(void)
{
  DB_MSG(("-->EchoPositionRange"));

  if(ParxRelsParHasValue("EchoPosition")==No)
  {
    EchoPosition=50.0;
  }
  else
  {
    EchoPosition = MAX_OF(MIN_OF(EchoPosition,50),20.0);
  }

  DB_MSG(("<--EchoPositionRange"));

}

void EchoPositionRel(void)
{
  DB_MSG(("-->EchoPositionRel"));

  EchoPositionRange();
  backbone();

  DB_MSG(("<--EchoPositionRel"));
}

/* -----------------------------------------------------------
 * Duration and amplitude of read spoiling gradient
 * ----------------------------------------------------------*/

void ReadSpoilGradRange()
{
  DB_MSG(("-->ReadSpoilGradRange"));

  if(!ParxRelsParHasValue("ReadSpoilGrad"))
  {
    ReadSpoilGrad = 40.0;
  }
  else
  {
    ReadSpoilGrad = 
      MIN_OF(ReadSpoilGrad,100.0);
    ReadSpoilGrad =
      MAX_OF(ReadSpoilGrad,0.0);
  }
  DB_MSG(("-->ReadSpoilGradRange"));
}

void ReadSpoilGradRel(void)
{
  DB_MSG(("-->ReadSpoilGradRel"));

  ReadSpoilGradRange();
  backbone();

  DB_MSG(("<--ReadSpoilGradRel"));
}


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

/* -----------------------------------------------------------
 * RF pulse related parameters
 * ----------------------------------------------------------*/


void ExcPulseEnumRel(void)
{
  DB_MSG(("-->ExcPulsesEnumRel"));
  
  /* set the name and clasification of ExcPulse: */

  STB_UpdateExcPulseName("ExcPulseEnum",
			 &ExcPulseEnum,
			 ExcPulse.Filename,
			 &ExcPulse.Classification);
  
  /* call the method relations */
  backbone();
  
  DB_MSG(("<--ExcPulseEnumRel"));                                       
}




void ExcPulseRange(void)
{
  DB_MSG(("-->ExcPulseRange"));
  
  if(ParxRelsParHasValue("ExcPulse") == No)
  {
    STB_InitRFPulse(&ExcPulse,
                    "bp.exc",
                    0.4,
                    20.0);
  }

  /* allowed clasification */
  
  switch(ExcPulse.Classification)
  {
    default:
      
      ExcPulse.Classification = LIB_EXCITATION;
      break;
    case LIB_EXCITATION:
    case PVM_EXCITATION:
    case USER_PULSE:
      break;
  }

  /* allowed angle for this pulse */
  
  ExcPulse.FlipAngle = MIN_OF(90.0,ExcPulse.FlipAngle);
  
  
  /* general verifiation of all pulse atributes  */
  
  STB_CheckRFPulse(&ExcPulse);
  
  DB_MSG(("<--ExcPulseRange"));
  
}


void ExcPulseRel(void)
{
  DB_MSG(("-->ExcPulseRel"));
  
  /*
   * Tell the request handling system that the parameter
   * ExcPulse has been edited 
   */
  
  UT_SetRequest("ExcPulse");
  
  /* Check the values of ExcPulse */
  
  ExcPulseRange();
  
  /* 
   * call the backbone; further handling will take place there
   * (by means of STB_UpdateRFPulse)  
   */
  
  backbone();
  
  DB_MSG(("<--ExcPulseRel"));
}



void DeriveGainsRange(void)
{
  DB_MSG(("-->DeriveGainsRange"));

  if(ParxRelsParHasValue("PVM_DeriveGains")==No)
  {
    PVM_DeriveGains = Yes;
  }
  else
  {
    switch(PVM_DeriveGains)
    {
      case No:
        break;
      default:
        PVM_DeriveGains = Yes;
      case Yes:
        break;
    }
  }


  DB_MSG(("<--DeriveGainsRange"));
  return;
}

void DeriveGainsRel(void)
{
  DB_MSG(("-->DeriveGainsRel"));

  DeriveGainsRange();
  backbone();

  DB_MSG(("<--DeriveGainsRel"));
  return;
}


/* -----------------------------------------------------------
 * Parameter NDummyScans controlling dummy scans
 * ----------------------------------------------------------*/

void NDummyScansRel(void)
{

  DB_MSG(("-->NDummyScansRel"));

  NDummyScansRange(); 
  backbone();

  DB_MSG(("<--NDummyScansRel"));

}

void NDummyScansRange(void)
{
  DB_MSG(("-->NDummyScansRange"));

  if(ParxRelsParHasValue("NDummyScans") == No)
    NDummyScans = 8;
  else
    NDummyScans = MAX_OF(0, NDummyScans);
  DB_MSG(("<--NDummyScansRange"));

} 

/* -----------------------------------------------------------
 * Parameter ShowAllPars controlling the visibility of non 
 * editable parameters in the method editor
 * ----------------------------------------------------------- */

void ShowAllParsRange(void)
{
  DB_MSG(("-->ShowAllParsRange"));

  if(!ParxRelsParHasValue("ShowAllPars"))
  {
    ShowAllPars=No;
  }
  

  DB_MSG(("<--ShowAllParsRange"));
}

void ShowAllParsRel(void)
{
  DB_MSG(("-->ShowAllParsRel"));

  ShowAllParsRange();
  backbone();
  DB_MSG(("<--ShowAllParsRel"));

}

void Local_RFSpoilingRelation(void)
{
 DB_MSG(("-->Local_RFSpoilingRelation\n"));

  if(RFSpoilerOnOff == Off)
  {
    //RFSpoilerdelay = 1.0;
    PARX_change_dims("RFSpoilerlist",1);
    MRT_RFSpoilFreqList(0.0,1,RFSpoilerlist,0.002);
  }
  if(RFSpoilerOnOff == On)
  {
    //RFSpoilerdelay = 1.0;
    PARX_change_dims("RFSpoilerlist",2048);
    MRT_RFSpoilFreqList(117,2048,RFSpoilerlist,0.002);
  }
  DB_MSG(("<--Local_RFSpoilingRelation\n"));
}