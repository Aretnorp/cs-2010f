<?

# Create the Socket
$sock = socket_create(AF_INET, SOCK_STREAM, 0);

# Create a directory
if(!is_dir($argv[2]))
{
    mkdir($argv[2]);
}

# Bind to the socket
socket_bind($sock, "127.0.0.1", intval($argv[1])) or die ("Could not bind to address\n");

# Listen for new connections
printf("Listening for connections . . .\n");
socket_listen($sock);

# Accept a new connection
$spawn = socket_accept($sock);

# Receive a file name
socket_recv($spawn, $file, 128, 0);

# Create the file
$file = fopen($argv[2] . "/" . $file, 'w+');

# Receive on the connection
while(($input = socket_recv($spawn, $buf, 1024, 0)) != 0)
{
    fwrite($file, $buf);
}

# Print the data
printf("Got this information: %s\n", $buf);

# Close the connection
socket_close($sock);

?>
