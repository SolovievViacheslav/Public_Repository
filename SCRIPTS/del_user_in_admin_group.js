/*
comp=GetObject("WinNT://"+WScript.Arguments.Item(0)+"/Администраторы");
WScript.Echo("WinNT://Castle/"+WScript.Arguments.Item(1));
comp.Remove("WinNT://Castle/"+WScript.Arguments.Item(1));
 */



var domain= new Enumerator(GetObject("WinNT://Castle"));

var user;
var excluded_comps=new Array(0);
//------------------------------------------------------------------------------------------------


function is_this_comp_exluded(comp_name)
{
 comp_name=String(comp_name);
 comp_name=comp_name.toUpperCase();
 var i;
 for(i=0;i<excluded_comps.lenght;i++)
	{
		if(comp_name==excluded_comps[i])return true;
	}

}
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
     	//WScript.Echo(comps_in_domain[i]);

   }
  }

 var err_msg="";
  for(i=0;i<comps_in_domain.lenght;i++)
  {
 	  if(is_this_comp_exluded(comps_in_domain[i])){WScript.Echo("Пропускаем"+" "+comps_in_domain[i]); continue;}
  	  else
     {
     	try
     	{
     	   WScript.Echo("Работаем с "+comps_in_domain[i]+"...");
     	   err_msg="Попытка удалить"+" "+user+" "+"из администраторов на"+" "+comps_in_domain[i];

     		comp=GetObject("WinNT://"+comps_in_domain[i]+"/Администраторы");
     		var admins=new Enumerator(comp.Members());
     		end_msg=":пользователь в списке админов не обнаружен";
     		for(;!admins.atEnd();admins.moveNext())
      	{
           		if(admins.item().Name==user)
               {
        				WScript.Echo("Найден на "+comps_in_domain[i]+"  "+admins.item().Name);
        				comp.Remove("WinNT://Castle/"+user);
        				end_msg=": Успешно";
        				break;
        			}

      	}


     	}
     	catch(e)
      {
        end_msg=": Ошибка. Комп выключен, или нет прав на выполнение операции";
      }
		err_msg+=end_msg;
      WScript.Echo(err_msg);
   }

  }
}

//-------------------------------------------------------------------------------
function init()
{
	if(WScript.Arguments.Count()!==0)
	{
		//первый аргумент командной строки - пользователь,  который будет админом
		user=WScript.Arguments.Item(0);
		//остальные параметры - компы на которых он админом не будет
		for(i=1;i<WScript.Arguments.Count();i++)
		{
			excluded_comps.lenght=i;
			excluded_comps[i-1]=String(WScript.Arguments.Item(i));
			excluded_comps[i-1]=excluded_comps[i-1].toUpperCase();
		}

	}else {WScript.Echo("Не заданы имя пользователя и исключенные машины");WScript.Quit();}
	WScript.Echo("=======================================");
	WScript.Echo("Admin: "+user);
	WScript.Echo("=======================================");
	WScript.Echo("Исключенные машины:");

	for(i=0;i<excluded_comps.lenght;i++)
	{
		WScript.Echo(excluded_comps[i]);
	}
	WScript.Echo("=======================================");
}

//======================================================================================
init();
add_user();
/*
for(;!namespace.atEnd();namespace.moveNext())
{
//для всех компов домена
if(namespace.item().Class=="Computer")
{
	WScript.Echo("Доавить"namespace.item().Name);
}
*/
