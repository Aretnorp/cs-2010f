<?

# Create the Socket
$sock = socket_create(AF_INET, SOCK_STREAM, 0);

# Connect the socket
socket_connect($sock, $argv[1], intval($argv[2]));

# Send the file name
socket_send($sock, $argv[3], strlen($argv[3]), 0);
sleep(1);

# Open the file
$file = fopen($argv[3], 'r') or die ("Could not open file\n");

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
