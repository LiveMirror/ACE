package DependencyWriterFactory;

# ************************************************************
# Description   : Create DependencyWriter objects.
# Author        : Chad Elliott
# Create Date   : 5/23/2003
# $Id: DependencyWriterFactory.pm 2036 2011-10-06 15:14:09Z johnnyw $
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

use DependencyWriter;

# ************************************************************
# Data Section
# ************************************************************

my $writers = {};

# ************************************************************
# Subroutine Section
# ************************************************************

sub register {
  $writers = shift;
}


sub create {
  return $$writers{$_[0]}->new() if (defined $$writers{$_[0]});

  print STDERR "WARNING: Invalid dependency writer type: $_[0]\n";
  return new DependencyWriter();
}


1;
