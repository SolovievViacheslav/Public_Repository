var domain= new Enumerator(GetObject("WinNT://Castle"));

var user;
var excluded_comps=new Array(0);
//-------------------------------------------------------------------------------
function add_user()
{
  var comps_in_domain=Array(0);
  var i=0;
  comps_in_domain.lenght=0;
  
  //занесем в массив все машины домена
  for(;!domain.atEnd();domain.moveNext())
  {

	   if(domain.item().Class=="Computer")
	   {
   		comps_in_domain.lenght++;
	   	comps_in_domain[i++]=domain.item().Name;
     		WScript.Echo(domain.item().Name);

	   }
   }

}

add_user();