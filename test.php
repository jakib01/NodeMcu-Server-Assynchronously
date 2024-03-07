<?php
// Define the IP address of your NodeMCU
$nodeMCUIP = "192.168.1.200"; // Replace with your NodeMCU's IP address

// Function to control the LED on the NodeMCU
function controlLED($status) {
    global $nodeMCUIP;
    $url = "http://" . $nodeMCUIP . "/control?control=" . $status;
    $response = file_get_contents($url);
    return $response;
}

// Check if the 'control' parameter is set in the request
if (isset($_GET['control'])) {
    $control = intval($_GET['control']);
    if ($control === 0 || $control === 1) {
        // Call the controlLED function with the received value
        $result = controlLED($control);
        echo $result; // Output the response from the NodeMCU
    } else {
        echo "Invalid control value";
    }
} else {
    echo "Control parameter not provided";
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED Control</title>
</head>
<body>
    <h2>LED Control</h2>
    <form action="" method="GET">
        <button type="submit" name="control" value="1">Turn On</button>
        <button type="submit" name="control" value="0">Turn Off</button>
    </form>
</body>
</html>
