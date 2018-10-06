eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 85142 2009-04-22 09:09:02Z vzykov $
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

my $client = PerlACE::TestTarget::create_target (1) || die "Create target 1 failed\n";

$CL = $client->CreateProcess ("client");

$test = $CL->SpawnWaitKill ($client->ProcessStartWaitInterval());

if ($test != 0) {
    print STDERR "ERROR: test returned $test\n";
    exit 1;
}

exit 0;
