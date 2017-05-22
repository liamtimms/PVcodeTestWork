/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/callbackDefs.h,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: callbackDefs.h,v 1.3.2.2 2007/07/26 19:27:14 mawi Exp $
 *
 * ***************************************************************/

/* ************************************************************
 * redirection of global parameter groups 
 * ***********************************************************/

/* inplane geometry                                          */
relations PVM_InplaneGeometryHandler  InplaneGeometryRel;

/* slice geometry:                                           */
relations PVM_SliceGeometryHandler    SliceGeometryRel;

/* nuclei                                                    */
relations PVM_NucleiHandler    backbone; 

/* digitizer parameter group                                 */
relations PVM_DigHandler       backbone;

/* encoding parameter group                                  */
relations PVM_EncodingHandler backbone;

/* ************************************************************
 * relation redirection of single global parameters used in
 * this method:
 * ***********************************************************/

//relations PVM_RepetitionTime          RepetitionTimeRel;
relations PVM_NAverages               AveragesRel;
relations PVM_EchoTime                EchoTimeRel;
relations PVM_MinEchoTime             backbone;

relations PVM_AcquisitionTime         backbone;
relations PVM_DeriveGains             DeriveGainsRel;
relations PVM_EffSWh                  EffSWhRel;

/* ************************************************************
 * parameters that are used but not shown in editor
 * only the method may change these parameters, they
 * are redirected to the backbone routine.
 * ************************************************************/

relations PVM_NRepetitions            backbone;     
relations PVM_MinRepetitionTime       backbone;
relations PVM_NEchoImages             backbone;
relations PVM_ExcPulseAngle           ExcPulseAngleRelation;

/* react on parameter adjustments */
relations PVM_AdjResultHandler backbone;
