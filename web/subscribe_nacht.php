<?php

$errorMsg = "";
if(count($_POST) != 0) {

	$ok = true;
	if(!isset($_POST['naam']) || $_POST['naam'] === "") {
		$ok = false;
		$errorMsg .= "De naam is verplicht!<br />";
	}
	if(!isset($_POST['voornaam']) || $_POST['voornaam'] === "") {
		$ok = false;
		$errorMsg .= "De voornaam is verplicht!<br />";
	}
	if(!isset($_POST['adres']) || $_POST['adres'] === "") {
		$ok = false;
		$errorMsg .= "Het adres is verplicht!<br />";
	}
	if(!isset($_POST['gemeente']) || $_POST['gemeente'] === "") {
		$ok = false;
		$errorMsg .= "De gemeente is verplicht!<br />";
	}
	if(!isset($_POST['email']) || $_POST['email'] === "") {
		$ok = false;
		$errorMsg .= "Het email-adres is verplicht!<br />";
	}
	if(!isset($_POST['telefoon']) || $_POST['telefoon'] === "") {
		$ok = false;
		$errorMsg .= "Het telefoon/gsm nummer is verplicht!<br />";
	}
	if(!isset($_POST['leeftijd']) || $_POST['leeftijd'] === "") {
		$ok = false;
		$errorMsg .= "De leeftijd is verplicht!<br />";
	}

	if ( $ok == true ) {


		$message =  "Beste,\r\nHierbij willen wij graag bevestigen dat ".$_POST['naam']." ".$_POST['voornaam'];
		$message .= " op de inschrijvingslijst geplaatst is voor de jeugdnacht op 17 mei 2013.\r\n";
		$message .= "\r\nDe inschrijving is echter nog niet actief.  De inschrijving wordt slechts actief";
		$message .= " indien u 3 euro stort op rekening BE57 8904 2405 5335. ";
		$message .= "Nadat onze medewerkers uw gegevens verwerkt hebben en uw betaling ontvangen hebben, ontvangt u een email met de definitieve bevestiging.";
		$message .= "\r\n\r\nMet vriendelijke groet,\r\n\r\nWerkgroep jeugdnacht 2013,\r\nSint-Laureins\r\n\r\n";
		foreach (array("naam","voornaam","adres","gemeente","telefoon","email","leeftijd") as $field) {
			$message .= "$field:\t".$_POST[$field]."\n";
		}	
		$leeftijd = (int)($_POST['leeftijd']);
		if ($leeftijd > 9) {
			$prefix = "1012";
		}
		foreach(array("1","2","3","4","reserve1","reserve2") as $suffix) {
			$message .= "workshop $suffix\t".$_POST["workshop".$prefix."_".$suffix]."\n";
		}
		$to = $_POST['email'];
		$from = "noreply@jeugddag.be";
		$headers = "From: $from\r\nCc: inschrijven@jeugddag.be\r\n";
		mail($to,"Inschrijvingsbevestiging Jeugdnacht",$message,$headers,"-f$from");

		$message2 = "Beste,\r\nIndien ".$_POST['naam']." ".$_POST['voornaam']." betaald heeft, \r\ndan klik je op onderstaande link.\r\n";
		$message2 .= "Is het niet mogelijk om op onderstaande link te klikken.  Kopieer hem naar de adresbalk van je browser.\r\n\r\n";
		$message2 .= "http://www.jeugddag.be/subscribe.php?paid=1&email=".urlencode($_POST['email'])."&naam=".urlencode($_POST['naam'])."&voornaam=".urlencode($_POST['voornaam']);
		$message2 .= "\r\n\r\nMet vriendelijke groet,\r\n\r\nDe website ;)\r\n";
		mail("inschrijven@jeugddag.be","Inschrijving Jeugdnacht: ".$_POST['naam']." ".$_POST['voornaam']." betaald?",$message2,"From: $from\r\n","-f$from");
		header("location: http://www.jeugddag.be/inschrijvingWachtende");
		die();
	} else {

	}
}
//	echo "<pre>";print_r($_REQUEST);echo "</pre>";
if(isset($_REQUEST['paid']) && isset($_REQUEST['email']) && isset($_REQUEST['naam']) && isset($_REQUEST['voornaam'])) {

	$naam = $_REQUEST['naam'];
	$voornaam = $_REQUEST['voornaam'];
	$message = "";
	$message .= "Beste,\r\n\r\nHierbij willen wij bevestigen dat we de betaling voor $naam $voornaam ontvangen hebben\r\n\r\n";
	$message .= "Met vriendelijke groet,\r\n\r\nWerkgroep jeugdnacht 2013,\r\nSint-Laureins\r\n\r\n";
	$header = "From: noreply@jeugddag.be\r\nCc: inschrijven@jeugddag.be";
	mail($_REQUEST['email'],"Betalingsbevestiging",$message,$header,"-fnoreply@jeugddag.be");

	die("OK");

}

?>
<html>
<head>
<title>jeugddag.be: Inschrijven jeugdnacht</title>
</head>
<body>

<script>
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

  ga('create', 'UA-40028920-1', 'jeugddag.be');
  ga('send', 'pageview');

</script>

<h1>Inschrijvingsformulier Jeugdnacht der verbroederde grensgemeenten 2013</h1>

<?php
if($errorMsg != "") {
	echo "<p style=\"color: red;border: 1px #FF2222\">$errorMsg</p>";
}
?>
<form action="subscribe_nacht.php" method="POST">

<table>
<tr><td><label for="naam">Naam</label></td><td><input type="text" id="naam" name="naam" value="<?php echo $_POST['naam'];?>" /></td><td>&nbsp;</td></tr>
<tr><td><label for="voornaam">Voornaam</label></td><td><input type="text" id="voornaam" name="voornaam" value="<?php echo $_POST['voornaam'];?>" /></td><td>&nbsp;</td></tr>
<tr><td><label for="adres">Adres (Straat/Nummer)</label></td><td><input type="text" id="adres" name="adres" value="<?php echo $_POST['adres'];?>" /></td><td>&nbsp;</td></tr>
<tr><td><label for="gemeente">Gemeente (Postcode/Gemeente)</label></td><td><input type="text" id="gemeente" name="gemeente" value="<?php echo $_POST['gemeente'];?>" /></td><td>&nbsp;</td></tr>
<tr><td><label for="telefoon">Telefoon/GSM nummer</label></td><td><input type="text" id="telefoon" name="telefoon" value="<?php echo $_POST['telefoon'];?>" /></td><td>&nbsp;</td></tr>
<tr><td><label for="email">Email</label></td><td><input type="text" id="email" name="email" value="<?php echo $_POST['email'];?>" /></td><td>&nbsp;</td></tr>
<tr><td><label for="leeftijd">Leeftijd</label></td><td><input type="text" id="leeftijd" name="leeftijd" onchange="processage(this)"  value="<?php echo $_POST['leeftijd'];?>" /></td><td>&nbsp;</td></tr>
</table>
</table>
<table>
<tr><td><input type="submit" /></td><td><a href="http://www.jeugddag.be/jeugdnacht">Annuleren</a></td></tr>
</table>
</form>
</body>
</html>
