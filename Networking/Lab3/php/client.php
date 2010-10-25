<?

# Create the Socket
$sock = socket_create(AF_INET, SOCK_STREAM, 0);

# Connect the socket
socket_connect($sock, '127.0.0.1', 1026);

# Open the file
$file = fopen('/usr/bin/vim', 'r') or die ('Could not open file');

# Send the data
while(!feof($file))
{
    $data = fread($file, 1024);
    socket_send($sock, $data, strlen($data), 0);
}

# Close the file
fclose($file);

# Close the socket
socket_close($sock);

?>
