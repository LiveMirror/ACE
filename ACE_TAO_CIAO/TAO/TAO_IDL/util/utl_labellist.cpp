// $Id: utl_labellist.cpp 95344 2011-12-15 18:05:15Z parsons $

/*

COPYRIGHT

Copyright 1992, 1993, 1994 Sun Microsystems, Inc.  Printed in the United
States of America.  All Rights Reserved.

This product is protected by copyright and distributed under the following
license restricting its use.

The Interface Definition Language Compiler Front End (CFE) is made
available for your use provided that you include this license and copyright
notice on all media and documentation and the software program in which
this product is incorporated in whole or part. You may copy and extend
functionality (but may not remove functionality) of the Interface
Definition Language CFE without charge, but you are not authorized to
license or distribute it to anyone else except as part of a product or
program developed by you or with the express written consent of Sun
Microsystems, Inc. ("Sun").

The names of Sun Microsystems, Inc. and any of its subsidiaries or
affiliates may not be used in advertising or publicity pertaining to
distribution of Interface Definition Language CFE as permitted herein.

This license is effective until terminated by Sun for failure to comply
with this license.  Upon termination, you shall destroy or return all code
and documentation for the Interface Definition Language CFE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED AS IS WITH NO WARRANTIES OF
ANY KIND INCLUDING THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF
DEALING, USAGE OR TRADE PRACTICE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED WITH NO SUPPORT AND WITHOUT
ANY OBLIGATION ON THE PART OF Sun OR ANY OF ITS SUBSIDIARIES OR AFFILIATES
TO ASSIST IN ITS USE, CORRECTION, MODIFICATION OR ENHANCEMENT.

SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES SHALL HAVE NO LIABILITY WITH
RESPECT TO THE INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY
INTERFACE DEFINITION LANGUAGE CFE OR ANY PART THEREOF.

IN NO EVENT WILL SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES BE LIABLE FOR
ANY LOST REVENUE OR PROFITS OR OTHER SPECIAL, INDIRECT AND CONSEQUENTIAL
DAMAGES, EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

Use, duplication, or disclosure by the government is subject to
restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227-7013 and FAR
52.227-19.

Sun, Sun Microsystems and the Sun logo are trademarks or registered
trademarks of Sun Microsystems, Inc.

SunSoft, Inc.
2550 Garcia Avenue
Mountain View, California  94043

NOTE:

SunOS, SunSoft, Sun, Solaris, Sun Microsystems or the Sun logo are
trademarks or registered trademarks of Sun Microsystems, Inc.

 */

// Implementation of a list of union labels.

// NOTE: This list class only works correctly because we use single public
//       inheritance, as opposed to multiple inheritance or public virtual.
//       It relies on a type-unsafe cast from UTL_List to subclasses, which
//       will cease to operate correctly if you use either multiple or
//       public virtual inheritance.

#include "utl_labellist.h"
#include "ast_union_label.h"
#include "ast_expression.h"
#include "ast_generator.h"

#include "global_extern.h"

#include "ace/OS_Memory.h"

UTL_LabelList::UTL_LabelList (AST_UnionLabel *s,
                              UTL_LabelList *cdr)
  : UTL_List (cdr),
    pd_car_data (s)
{
}

// Get list item.
AST_UnionLabel *
UTL_LabelList::head (void)
{
  return this->pd_car_data;
}

// Copy a label list.
UTL_LabelList *
UTL_LabelList::copy (void)
{
  AST_Expression *val = this->pd_car_data->label_val ();

  AST_Expression *val_copy = 0;
  ACE_NEW_RETURN (val_copy,
                  AST_Expression (val, val->ev ()->et),
                  0);

  AST_UnionLabel *label_copy =
    idl_global->gen ()->create_union_label (this->pd_car_data->label_kind (),
                                            val_copy);

  UTL_LabelList *retval = 0;
  ACE_NEW_RETURN (retval,
                  UTL_LabelList (label_copy,
                                 0),
                  0);

  if (this->tail () != 0)
    {
      retval->nconc ((UTL_LabelList *) this->tail ()->copy ());
    }

  return retval;
}

void
UTL_LabelList::destroy (void)
{
  this->pd_car_data->destroy ();
  delete this->pd_car_data;
  this->pd_car_data = 0;

  this->UTL_List::destroy ();
}

UTL_LabellistActiveIterator::UTL_LabellistActiveIterator (UTL_LabelList *s)
  : UTL_ListActiveIterator (s)
{
}

// Get current item.
AST_UnionLabel *
UTL_LabellistActiveIterator::item (void)
{
  if (this->source == 0)
    {
      return 0;
    }

  UTL_LabelList *llist = dynamic_cast<UTL_LabelList *> (this->source);

  return (llist != 0 ? llist->head () : 0);
}

