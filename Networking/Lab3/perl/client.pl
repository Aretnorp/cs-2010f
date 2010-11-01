use IO::Socket;

# Open the Socket
my $sock = new IO::Socket::INET 
(
    PeerAddr => $ARGV[0],
    PeerPort => $ARGV[1],
    Proto    => 'tcp',
);
die "Could not create socket: $!\n" unless $sock;

# Send the file name
print "Client has: $ARGV[2] \n";
print $sock $ARGV[2];

# Open the file
open FILE, "<$ARGV[2]" or die $!;

# Send the information
print $sock <FILE>;

# Close the socket
close($sock)
