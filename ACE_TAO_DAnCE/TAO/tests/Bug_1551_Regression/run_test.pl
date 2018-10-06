eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# $Id: run_test.pl 87910 2009-12-04 09:16:48Z dbudko $
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

$status = 0;
$debug_level = '0';
$quick = 0;

foreach $i (@ARGV) {
    if ($i eq '-debug') {
        $debug_level = '10';
    } elsif ($i eq '-quick') {
        $quick = 1;
    }
}

my $server = PerlACE::TestTarget::create_target (1) || die "Create target 1 failed\n";
my $client1 = PerlACE::TestTarget::create_target (2) || die "Create target 2 failed\n";
my $client2 = PerlACE::TestTarget::create_target (3) || die "Create target 3 failed\n";
my $client3 = PerlACE::TestTarget::create_target (4) || die "Create target 4 failed\n";

my $iorbase = "server.ior";
my $server_iorfile = $server->LocalFile ($iorbase);
my $client1_iorfile = $client1->LocalFile ($iorbase);
my $client2_iorfile = $client2->LocalFile ($iorbase);
my $client3_iorfile = $client3->LocalFile ($iorbase);
$server->DeleteFile($iorbase);
$client1->DeleteFile($iorbase);
$client2->DeleteFile($iorbase);
$client3->DeleteFile($iorbase);

$SV = $server->CreateProcess ("server",
                              "-ORBdebuglevel $debug_level ".
                              "-ORBdotteddecimaladdresses 1 ".
                              "-o $server_iorfile");
$CL1 = $client1->CreateProcess ("client", "-k file://$client1_iorfile");
$CL2 = $client2->CreateProcess ("client", "-k file://$client2_iorfile");
$CL3 = $client3->CreateProcess ("client", "-k file://$client3_iorfile");

local $ntimes = 50 ; # run test for 50 times

if ($quick)  {
    $ntimes = 1;
}

local $n = 0;

while($n < $ntimes) {
    print STDERR " Going .. \n";

    $server_status = $SV->Spawn ();

    if ($server_status != 0) {
        print STDERR "ERROR: server returned $server_status\n";
        exit 1;
    }

    if ($server->WaitForFileTimed ($iorbase,
                                   $server->ProcessStartWaitInterval()) == -1) {
        print STDERR "ERROR: cannot find file <$server_iorfile>\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }

    if ($server->GetFile ($iorbase) == -1) {
        print STDERR "ERROR: cannot retrieve file <$server_iorfile>\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }
    if ($client1->PutFile ($iorbase) == -1) {
        print STDERR "ERROR: cannot set file <$client1_iorfile>\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }
    if ($client2->PutFile ($iorbase) == -1) {
        print STDERR "ERROR: cannot set file <$client2_iorfile>\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }
    if ($client3->PutFile ($iorbase) == -1) {
        print STDERR "ERROR: cannot set file <$client3_iorfile>\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }

    $client_status = $CL1->Spawn ();
    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }

    $client_status = $CL2->Spawn ();
    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        $SV->Kill (); $SV->TimedWait (1);
        $CL1->Kill (); $CL1->TimedWait (1);
        exit 1;
    }

    $client_status = $CL3->Spawn ();
    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        $SV->Kill (); $SV->TimedWait (1);
        $CL1->Kill (); $CL1->TimedWait (1);
        $CL2->Kill (); $CL2->TimedWait (1);
        exit 1;
    }

    sleep (30);

    $server_status = $SV->WaitKill ($server->ProcessStopWaitInterval() + 15);
    if ($server_status < 0) {
        print STDERR "ERROR: server returned $server_status\n";
        $CL1->Kill (); $CL1->TimedWait (1);
        $CL2->Kill (); $CL2->TimedWait (1);
        $CL3->Kill (); $CL3->TimedWait (1);
        exit 1;
    }

    $client_status = $CL1->WaitKill ($client1->ProcessStopWaitInterval());
    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        $CL2->Kill (); $CL2->TimedWait (1);
        $CL3->Kill (); $CL3->TimedWait (1);
        exit 1;
    }

    $client_status = $CL2->WaitKill ($client2->ProcessStopWaitInterval());
    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        $CL3->Kill (); $CL3->TimedWait (1);
        exit 1;
    }

    $client_status = $CL3->WaitKill ($client3->ProcessStopWaitInterval());
    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        exit 1;
    }

    $server->DeleteFile($iorbase);
    $client1->DeleteFile($iorbase);
    $client2->DeleteFile($iorbase);
    $client3->DeleteFile($iorbase);

    $n = $n + 1;
}

$server->DeleteFile($iorbase);
$client1->DeleteFile($iorbase);
$client2->DeleteFile($iorbase);
$client3->DeleteFile($iorbase);

exit $status;
