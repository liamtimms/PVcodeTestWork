/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/loadMeth.c,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: loadMeth.c,v 1.1.6.2 2007/10/18 09:38:10 mawi Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: loadMeth.c,v 1.1.6.2 2007/10/18 09:38:10 mawi Exp $ (C) 2007 Bruker BioSpin MRI GmbH";

#define DEBUG		    0
#define DB_MODULE	  0
#define DB_LINE_NR	0


#include "method.h"


void loadMeth(const char *className)
{
  DB_MSG(( "-->loadMeth( %s )", className ));


  if ( (0 != className) && ( 0 == strcmp( className, "MethodClass" ))) 
  {
    initMeth();
  }
  else
  {
    DB_MSG(( "...ignoring loadMeth call - I don't know this class" ));
  }

  DB_MSG(( "<--loadMeth( %s )", className ));
}

/* ***************************************************************/
/*		E N D   O F   F I L E				 */
/* ***************************************************************/


