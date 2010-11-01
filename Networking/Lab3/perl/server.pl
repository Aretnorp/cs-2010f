use IO::Socket;

# Open the Socket
my $sock = new IO::Socket::INET 
(
    LocalAddr => '127.0.0.1',
    LocalPort => $ARGV[0],
    Proto    => 'tcp',
    Listen   => 1,
    Reuse    => 1,
);
die "Could not create socket: $!\n" unless $sock;

# Receive the information
my $client_sock = $sock->accept();

# Receive the file
$client_sock->recv($name, 128);

# Create the directory
unless(-d $ARGV[1])
{
    mkdir $ARGV[1] or die $!;
}

# Open the file for writing
print STDOUT "Server has >" . "$name\n";
open FILE, ">", "$ARGV[1]/$name" or die $!;

# Receive the contents of the file
while(<$client_sock>)
{
    print FILE $_;
}

# Close the socket
close($sock)
