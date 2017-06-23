/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/demo/gre/RecoRelations.c,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: RecoRelations.c,v 1.3 2013/09/06 12:38:39 sako Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: RecoRelations.c,v 1.3 2013/09/06 12:38:39 sako Exp $ (C) 2007 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR	0


#include "method.h"

void SetRecoParam( void )

{
  
  DB_MSG(("-->SetRecoParam"));

  /* set baselevel reconstruction parameters */
  
  int dim = PTB_GetSpatDim();
  int echoImages = PVM_NEchoImages;

  ATB_InitUserModeReco(
    dim,
    0,
    PVM_EncMatrix,
    PVM_Matrix,
    PVM_AntiAlias,
    PVM_EncPftOverscans,
    NI,
    ACQ_obj_order,
    ACQ_phase_factor,
    PVM_EncSteps1,
    PVM_EncSteps2,
    NULL,
    PVM_EncNReceivers,
    PVM_EncChanScaling,
    PVM_EncPpiRefLines[1],
    PVM_EncPpi[1]);

  ATB_SetRecoRotate(
    NULL,
    PVM_Fov[0] * PVM_AntiAlias[0],
    NSLICES,
    echoImages,
    0);

  ATB_SetRecoRotate(
    PVM_EffPhase1Offset,
    PVM_Fov[1] * PVM_AntiAlias[1],
    NSLICES,
    echoImages,
    1);

  if (dim == 3)
  {
    ATB_SetRecoRotate(
      PVM_EffPhase2Offset,
      PVM_Fov[2] * PVM_AntiAlias[2],
      NSLICES,
      echoImages,
      2);
  }

  ATB_SetRecoPhaseCorr(PVM_EchoPosition, 0.0, 0);
  for (int i = 1; i < dim; i++)
  {
    ATB_SetRecoPhaseCorr(50.0, 0.0, i);
  }

  ATB_SetRecoTranspositionFromLoops(
    PtrType3x3 ACQ_grad_matrix[0],
    NSLICES,
    echoImages,
    NI,
    ACQ_obj_order);
  
  
  DB_MSG(("<--SetRecoParam"));
  
}

