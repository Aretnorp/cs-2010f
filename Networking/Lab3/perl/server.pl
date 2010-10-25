use IO::Socket;

# Open the Socket
my $sock = new IO::Socket::INET 
(
    LocalAddr => '127.0.0.1',
    LocalPort => '1024',
    Proto    => 'tcp',
    Listen   => 1,
    Reuse    => 1,
);
die "Could not create socket: $!\n" unless $sock;

# Open the file for writing
open FILE, ">testing" or die $!;

# Receive the information
my $client_sock = $sock->accept();
while(<$client_sock>)
{
    print FILE $_;
}

# Close the socket
close($sock)
