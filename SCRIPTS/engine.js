/*
	Отправляет почту на указанный адрес с
	прикрепленным файлом
*/
//Создаем объект WshShell
WshShell = WScript.CreateObject("WScript.Shell");
var fso=WScript.CreateObject("Scripting.FileSystemObject");
var f_name;
//размер файла отчета без единой записи (пустая форма)
var f_empty_size=1266;
var letter_body;

if(WScript.Arguments.Count()!==0)f_name=WScript.Arguments.Item(0);
else{WScript.Echo("Не задано имя файла");WScript.Quit();}

letter_body="Detected files list in attachment";
//-------------------------------------------------------------------------------------------------

//отправляет почту утилитой Blat
function SendMailBlat(usr_soname,theme,body,f_attachmet)
{
 	var recipient="";
 	var option_attachment="";

 	if(f_attachmet!=undefined)
 	{

	     if (!fso.FileExists(f_attachmet))
	     {
	     	WScript.Echo("WARNING: attach "+f_attachmet + " not exists");
	 		WScript.Quit();
	     }
	     else
	     {
	     	option_attachment="-attach "+f_attachmet;
	     }

 	}
 	if(usr_soname==undefined)
 	{
 		WScript.Echo("WARNING: RECIPIENTS UNDEFINED");
 		WScript.Quit();
 	}
	else 
	{
	 	usr_soname="Soloviev";
	 	recipient=usr_soname;
 	}

 	var str_exe="blat.exe -to "+ recipient+
					" -f "+"System_Notification"+
					" -server se.temple.in "+
					" -subject "+"\""+theme+"\""+
					" -body "+"\""+body+"\""+
					" "+option_attachment;

 	WScript.Echo(str_exe);

	WshShell.Exec(str_exe);

    WScript.Sleep (500);

}
//-----------------------------------------------------------------------------------------------
f=fso.GetFile(f_name);
var recipients=new Array(1);
recipients[0]="Soloviev";

if(f.Size>f_empty_size)
{
	SendMailBlat(recipients,"X Files",letter_body,f.Path);
}
else
{
  WScript.Echo("f.Size>f_empty_size");
}  