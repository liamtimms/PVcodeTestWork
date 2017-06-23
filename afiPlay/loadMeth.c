/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/demo/gre/loadMeth.c,v $
 *
 * Copyright (c) 2007 - 2010
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: loadMeth.c,v 1.2 2013/04/25 14:36:02 cmei Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: loadMeth.c,v 1.2 2013/04/25 14:36:02 cmei Exp $ (C) 2007 - 2010 Bruker BioSpin MRI GmbH";

#define DEBUG		    0
#define DB_MODULE	  0
#define DB_LINE_NR	0


#include "method.h"


void loadMeth(const char *className)
{
  DB_MSG(( "-->gre:loadMeth( %s )", className ));


  if (0 != className)
  {
      if (0 == strcmp( className, "MethodClass"))
      {
          initMeth();
      }
      else if (0 == strcmp(className, "MethodRecoGroup"))
      {
          DB_MSG(("...responding to loadMeth call for MethodRecoGroup."));
      }
  }
  else
  {
    DB_MSG(( "...ignoring loadMeth call - I don't know this class" ));
  }

  DB_MSG(( "<--gre:loadMeth( %s )", className ));
}

/* ***************************************************************/
/*		E N D   O F   F I L E				 */
/* ***************************************************************/


