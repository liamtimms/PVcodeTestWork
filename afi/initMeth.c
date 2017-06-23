/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/initMeth.c,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: initMeth.c,v 1.3.2.4 2009/09/10 16:15:32 mawi Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: initMeth.c,v 1.3.2.4 2009/09/10 16:15:32 mawi Exp $ (c) 2007 Bruker BioSpin MRI GmbH";

#define DEBUG		    0
#define DB_MODULE   0
#define DB_LINE_NR	0


#include "method.h"

void initMeth()
{
  int dimRange[2] = { 2,3 };
  int lowMat[3]   = { 32, 8, 8 };
  int upMat[3]    = { 1024, 1024, 256 };

  DB_MSG(( "--> initMeth" ));

  /* Set Version number of current method                       */

  PTB_VersionRequirement( Yes,20090101,"");

  /* initialization of PVM_Nucleus1                             */

  STB_InitNuclei(1);

  /* RF Pulse initialization                                    */

  ExcPulseRange();
  DeriveGainsRange();
  STB_InitExcPulseEnum("ExcPulseEnum");
  ParxRelsShowInEditor("PVM_ExcPulseAngle");

  ParxRelsMakeNonEditable("afi_total_TR");

  /* initialize duration of phase encoding gradient             */
  EncGradDurRange();

  /* init frequency encoding parameters                         */
  EffSWhRange();
  EchoPositionRange();
  ReadSpoilGradRange();
  ReadSpoilGradDurRange();
  STB_InitDigPars();

  /* init inplane geometry parameters                           */
  STB_InitStandardInplaneGeoPars(2,dimRange,lowMat,upMat,No);

  /* init slice geometry parameters                             */
  STB_InitSliceGeoPars(0,0,0);

  /* init encoding parameters                                   */
  STB_InitEncoding();

  /* init spectroscopy parameters (no csi)                      */
  PTB_SetSpectrocopyDims( 0, 0 );

  /* initialize standard imaging parameters NA TR TE DS         */
  afi_TR1Range();
  afi_TR2Range();
  afi_total_TRRange();
  AveragesRange();
  EchoTimeRange();
  NDummyScansRange();


    if(ParxRelsParHasValue("RFSpoilerOnOff") == 0)
    RFSpoilerOnOff = Off; 


  /* showParam initialization                                   */
  ShowAllParsRange();

 
  /* Once all parameters have initial values, the backbone is 
   * called to assure they are consistent                       */
  
  backbone();
 
  DB_MSG(( "<-- initMeth" ));
}

/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/


