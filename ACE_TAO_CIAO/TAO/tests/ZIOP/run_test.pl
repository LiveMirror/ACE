eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# $Id: run_test.pl 88213 2009-12-17 11:48:32Z dbudko $
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

$status = 0;
$debug_level = '0';

foreach $i (@ARGV) {
    if ($i eq '-debug') {
        $debug_level = '10';
    }
}

my $server = PerlACE::TestTarget::create_target (1) || die "Create target 1 failed\n";
my $client = PerlACE::TestTarget::create_target (2) || die "Create target 2 failed\n";

my $iorbase = "server.ior";
my $server_iorfile = $server->LocalFile ($iorbase);
my $client_iorfile = $client->LocalFile ($iorbase);


for ($test = 1; $test <= 4 && $status == 0; ++$test){
    $server->DeleteFile($iorbase);
    $client->DeleteFile($iorbase);

    $SV = $server->CreateProcess ("server", "-o $server_iorfile -t $test -ORBdebuglevel $debug_level");
    $CL = $client->CreateProcess ("client", "-k file://$client_iorfile -t $test -ORBdebuglevel $debug_level");
    $server_status = $SV->Spawn ();

    print "\n\n\n====== START TEST $test/4 ======\n\n\n";

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
    if ($client->PutFile ($iorbase) == -1) {
        print STDERR "ERROR: cannot set file <$client_iorfile>\n";
        $SV->Kill (); $SV->TimedWait (1);
        exit 1;
    }

    $client_status = $CL->SpawnWaitKill ($client->ProcessStartWaitInterval());

    if ($client_status != 0) {
        print STDERR "ERROR: client returned $client_status\n";
        $status = 1;
    }

    $server_status = $SV->WaitKill ($server->ProcessStopWaitInterval());

    if ($server_status != 0) {
        print STDERR "ERROR: server returned $server_status\n";
        $status = 1;
    }
    $server->DeleteFile($iorbase);
    $client->DeleteFile($iorbase);
}

$server->GetStderrLog();
$client->GetStderrLog();

$server->DeleteFile($iorbase);
$client->DeleteFile($iorbase);

exit $status;
