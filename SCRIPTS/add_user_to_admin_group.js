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

  //������� � ������ ��� ������ ������
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
 	  if(is_this_comp_exluded(comps_in_domain[i])){WScript.Echo("����������"+" "+comps_in_domain[i]); continue;}
  	  else
     {
     	try
     	{
     	   WScript.Echo("�������� � "+comps_in_domain[i]+"...");
     	   err_msg="������� ��������"+" "+user+" "+"� �������������� ��"+" "+comps_in_domain[i];
     		comp=GetObject("WinNT://"+comps_in_domain[i]+"/��������������");
     		comp.Add("WinNT://Castle/"+user);
     		//err_msg="������������"+" "+user+" "+"������� ��� �������� � �������������� ��"+" "+comps_in_domain[i];
     		err_msg+=": �������";
     	}
     	catch(e)
      {
       //err_msg="ERROR! ������������"+" "+user+" "+"�� ��� �������� � �������������� ��"+" "+comps_in_domain[i]+" "+e.description;
        err_msg+=": ������";
      }

      WScript.Echo(err_msg);
   }

  }
}

//-------------------------------------------------------------------------------
function init()
{
	if(WScript.Arguments.Count()!==0)
	{
		//������ �������� ��������� ������ - ������������,  ������� ����� �������
		user=WScript.Arguments.Item(0);
		//��������� ��������� - ����� �� ������� �� ������� �� �����
		for(i=1;i<WScript.Arguments.Count();i++)
		{
			excluded_comps.lenght=i;
			excluded_comps[i-1]=String(WScript.Arguments.Item(i));
			excluded_comps[i-1]=excluded_comps[i-1].toUpperCase();
		}

	}else {WScript.Echo("�� ������ ��� ������������ � ����������� ������");WScript.Quit();}
	WScript.Echo("=======================================");
	WScript.Echo("Admin: "+user);
	WScript.Echo("=======================================");
	WScript.Echo("����������� ������:");

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
//��� ���� ������ ������
if(namespace.item().Class=="Computer")
{
	WScript.Echo("�������"namespace.item().Name);
}
*/
