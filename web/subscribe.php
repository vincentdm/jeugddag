<?php

if(count($_POST) != 0) {

	$message =  "Beste,\r\nHierbij willen wij graag bevestigen dat ".$_POST['naam']." ".$_POST['voornaam'];
	$message .= " op de inschrijvingslijst geplaatst is voor de jeugddag op 18 mei 2013.\r\n";
	$message .= "\r\nDe inschrijving is echter nog niet actief.  De inschrijving wordt slechts actief";
	$message .= " indien u 5 euro stort op rekening BE57 8904 2405 5335 of in gesloten envelop afgeeft op uw lokale jeugddienst.";
	$message .= "Nadat onze medewerkers uw gegevens verwerkt hebben en uw betaling ontvangen hebben, ontvangt u een email met de definitieve bevestiging.";
	$message .= "\r\n\r\nMet vriendelijke groet,\r\n\r\nWerkgroep jeugddag 2013,\r\nSint-Laureins\r\n\r\n";
	foreach (array("naam","voornaam","adres","telefoon","email","leeftijd","vriendje","opstapplaats") as $field) {
		$message .= "$field:\t".$_POST[$field]."\n";
	}	
	$prefix = "69";
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
	mail($to,"Inschrijvingsbevestiging",$message,$headers,"-f$from");

	$message2 = "Beste,\r\nIndien ".$_POST['naam']." ".$_POST['voornaam']." betaald heeft, \r\ndan klik je op onderstaande link.\r\n";
	$message2 .= "Is het niet mogelijk om op onderstaande link te klikken.  Kopieer hem naar de adresbalk van je browser.\r\n\r\n";
	$message2 .= "http://www.jeugddag.be/subscribe.php?paid=1&email=".$_POST['email']."&naam=".$_POST['naam']."&voornaam=".$_POST['voornaam'];
	$message2 .= "\r\n\r\nMet vriendelijke groet,\r\n\r\nDe website ;)\r\n";
	mail("inschrijven@jeugddag.be","Inschrijving: ".$_POST['naam']." ".$_POST['voornaam']." betaald?",$message2,"From: $from\r\n","-f$from");
	header("location: http://www.jeugddag.be/inschrijvingWachtende");
	die();
}
//	echo "<pre>";print_r($_REQUEST);echo "</pre>";
if(isset($_REQUEST['paid']) && isset($_REQUEST['email']) && isset($_REQUEST['naam']) && isset($_REQUEST['voornaam'])) {

	$naam = $_REQUEST['naam'];
	$voornaam = $_REQUEST['voornaam'];
	$message = "";
	$message .= "Beste,\r\n\r\nHierbij willen wij bevestigen dat we de betaling voor $naam $voornaam ontvangen hebben\r\n\r\n";
	$message .= "Met vriendelijke groet,\r\n\r\nWerkgroep jeugddag 2013,\r\nSint-Laureins\r\n\r\n";
	$header = "From: noreply@jeugddag.be\r\nCc: inschrijven@jeugddag.be";
	mail($_REQUEST['email'],"Betalingsbevestiging",$message,$header,"-fnoreply@jeugddag.be");

	die("OK");

}
$workshops69 = array();
$workshops69[] .= "";
$workshops69[] .= "Geheime vaart";
$workshops69[] .= "Knal op de bal";
$workshops69[] .= "Maak je eigen Sam";
$workshops69[] .= "Muziektheater";
$workshops69[] .= "Ponyverzorging";
$workshops69[] .= "Smokkelbrandjes blussen";
$workshops69[] .= "Smokkelslieren";
$workshops69[] .= "Smokkelspelen";
$workshops69[] .= "Smokkelspringen";
$workshops69[] .= "Superspecialespelen";
$workshops69[] .= "Velocross";
$workshops69[] .= "Wateronderzoek";

$workshops1012 = array();
$workshops1012[] .= "";
$workshops1012[] .= "Kajak";
$workshops1012[] .= "Knal op de bal";
$workshops1012[] .= "Mountainbike";
$workshops1012[] .= "Orientatieloop";
$workshops1012[] .= "Paardrijden";
$workshops1012[] .= "Powerkite";
$workshops1012[] .= "Rappen";
$workshops1012[] .= "Reuzenspelen";
$workshops1012[] .= "Smokkelspelen";
$workshops1012[] .= "Standup peddeling";
$workshops1012[] .= "Survival";
$workshops1012[] .= "Vlottentocht";



?>
<html>
<head>
<title>jeugddag.be: Inschrijven</title>
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
<script>
function processage(field) {
  table69 = document.getElementById("table69");
  table1012 = document.getElementById("table1012");

	  if(field.value < 10) {
		table69.style.display="block";
		table1012.style.display="none";
	  } else { 
		table69.style.display="none";
		table1012.style.display="block";
	}
}
</script>

<h1>Inschrijvingsformulier Jeugddag der verbroederde grensgemeenten 2013</h1>
<form action="subscribe.php" method="POST">

<table>
<tr><td><label for="naam">Naam</label></td><td><input type="text" id="naam" name="naam" /></td></tr>
<tr><td><label for="voornaam">Voornaam</label></td><td><input type="text" id="voornaam" name="voornaam" /></td></tr>
<tr><td><label for="adres">Adres (Straat/Nummer/Postcode/Gemeente)</label></td><td><input type="text" id="adres" name="adres" /></td></tr>

<tr><td><label for="telefoon">Telefoon/GSM nummer</label></td><td><input type="text" id="telefoon" name="telefoon" /></td></tr>
<tr><td><label for="email">Email</label></td><td><input type="text" id="email" name="email" /></td></tr>
<tr><td><label for="leeftijd">Leeftijd</label></td><td><input type="text" id="leeftijd" name="leeftijd" onchange="processage(this)" /></td></tr>
<tr><td><label for="vriendje">Naam van het vriendje bij <br/>wie ik zeker wil zitten</label></td><td><input type="text" id="vriendje" name="vriendje" /></td></tr>
<tr><td><label for="opstapplaats">Ik ga met de bus en stap op in <br/>(indien niet van Sint-Laureins)</label></td><td><input type="text" id="opstapplaats" name="opstapplaats" /></td></tr>
</table>
<table id="table69" style="display: none">
<?php
foreach (array("1","2","3","4","reserve1","reserve2") as $num) {
?>

<tr><td><label for="workshop69_<?php echo $num;?>">Workshop <?php echo $num;?>:</label></td><td>
	<select id="workshop69_<?php echo $num;?>" name="workshop69_<?php echo $num;?>">
<?php
	foreach ($workshops69 as $workshop) {
		echo "<option value=\"$workshop\">$workshop</option>";
	}
?>
	</select>
</td></tr>
<?php
}
?>
</table>
<table id="table1012" style="display:none">
<?php
foreach (array("1","2","3","4","reserve1","reserve2") as $num) {
?>

<tr><td><label for="workshop1012_<?php echo $num;?>">Workshop <?php echo $num;?>:</label></td><td>
	<select id="workshop1012_<?php echo $num;?>" name="workshop1012_<?php echo $num;?>">
<?php
	foreach ($workshops1012 as $workshop) {
		echo "<option value=\"$workshop\">$workshop</option>";
	}
?>
	</select>
</td></tr>
<?php
}
?>
</table>
<table>
<tr><td><input type="submit" /></td><td><a href="http://www.jeugddag.be/inschrijven">Annuleren</a></td></tr>
</table>
</form>
</body>
</html>
