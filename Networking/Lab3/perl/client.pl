use IO::Socket;

# Open the Socket
my $sock = new IO::Socket::INET 
(
    PeerAddr => '127.0.0.1',
    PeerPort => '1024',
    Proto    => 'tcp',
);
die "Could not create socket: $!\n" unless $sock;

# Open the file
open FILE, "</usr/bin/vim" or die $!;

# Send the information
print $sock <FILE>;

# Close the socket
close($sock)
