
//Создаем объект WshShell
WshShell = WScript.CreateObject("WScript.Shell");
var fso;  //Объявляем переменные
var f_letter;
var f_letter_tmp;
var f_log_name="tmp.log"
var f_log;
//Создаем объект FileSystemObject
fso=WScript.CreateObject("Scripting.FileSystemObject");
//Генерируем случайное имя файла
f_letter_name="letter_body.txt"
f_letter_tmp_name="tmp112233.txt"


//f_log=fso.CreateTextFile(f_letter_name, true); 
//f_log.Write("Start\n");
/*var usr_soname="";
WScript.Echo(usr_soname.length);
WScript.Quit();
/*
body="123"
	WshShell.Exec("bmail.exe -s se.temple.in -t "+ "Soloviev@temple.in"+"-f Soloviev@temple.in "+
					" -a Странное "+
					 "-b "+ body);
WScript.Quit();
*/

var fso=WScript.CreateObject("Scripting.FileSystemObject");
var outlook=WScript.CreateObject("Outlook.Application");
var msg=outlook.CreateItem(0);
var folder=fso.GetFolder("X:\\");

var users=new Enumerator(folder.SubFolders);

var tmp=0;
var without_profiles_users="";
var access_error_users="";
var critical_size=10;
var mb=1024*1024;
var letter_body="";

var target_dirs;
target_dirs=new Array(1);
var tmp=0;
//target_dirs[tmp++]="Private";
target_dirs[tmp++]="Profiles";
target_dirs[tmp++]="ProfileTs";
target_dirs[tmp++]="Profiles.V2";
target_dirs[tmp++]="Profiles.V6";


if(WScript.Arguments.Count()!==0)critical_size=WScript.Arguments.Item(0);
else{WScript.Echo("Не задан допустимый размер профиля");WScript.Quit();}

//letter_body="Размер вашего профиля превышает допустимый размер "+"("+critical_size+" МБ"+")";
//letter_body+="\nУменьшите размер профиля.";

//-------------------------------------------------------------------------------------------------
function create_obj(name,problem_dir_name,size)
{
var a=new Object();
	a.name=name;
	a.size=size;
	a.problem_dir_name=problem_dir_name;
	return a;
}
//-------------------------------------------------------------------------------------------------
function sort(arr)
{
var fl=1;
var tmp;

	for(i2=0;i2<arr.length;i2++)
	{
		for(i=0;i<arr.length-1;i++)
		{
	  		if(arr[i+1].size>arr[i].size)
     		{
      			tmp=arr[i];
	      		arr[i]=arr[i+1];
    	  		arr[i+1]=tmp;
      			fl=1;
     		}
     		else fl=0;
		}
		if(i2>0 && fl==1)i2--;
	}
return arr;
}

//-------------------------------------------------------------------------------------------------
//отправляет почту аутлуком
function SendMailOutlook(usr_soname,theme,body)
{

 msg=outlook.CreateItem(0);

 if(usr_soname.length==undefined)msg.to=usr_soname+"@temple.in";
 else for(i=0;i<usr_soname.length;i++)
 {
	WScript.Echo("i:",i);
 	msg.Recipients.Add(usr_soname[i].name+"@temple.in");
 	//WScript.Echo(usr_soname[i].name+"@temple.in");
 }

 msg.Subject=theme;
 msg.Body=body;
 msg.Importance=2;
 //msg.display();
 msg.Send();

}
//отправляет почту утилитой bmail
/*f_or_body: 1-тело письма из файла (f_body),
			 2-(любое другое значение) f_body - строка-тело письма */
function SendMailBmail(usr_soname,theme,f_or_body,f_body)
{
 	var recipient="";
 	var f_body_tmp=f_body;

 	if(usr_soname==undefined)
 	{
 		WScript.Echo("WARNING: RECIPIENTS UNDEFINED");
 		WScript.Quit();
 	}
	else 
	{
	 	//usr_soname="Soloviev";
	 	recipient=usr_soname+"@temple.in"
 	}


 	/*если тело просто сообщение то создадим временный файл,
 	в него запишем сообщение, оправим из него, потом удалим*/
 	if(f_or_body!=1)
 	{
	 	f_letter_tmp=fso.CreateTextFile(f_letter_tmp_name, true); 
	 	f_letter_tmp.Write(f_body);
        f_letter_tmp.Close();

 		f_body_tmp=f_letter_tmp_name;
 	}
   
	WshShell.Exec("bmail.exe -s se.temple.in -t "+ recipient+
					" -f "+"System_Notification"+
					" -a "+"\""+theme+"\""+
					" -m "+"\""+f_body_tmp+"\"");
    WScript.Sleep (500);

}

//-------------------------------------------------------------------------------------------------

function get_overflow_profile_users(critical_size)
{
   users_out=new Array(0);
   var cntr=0;

    while(users.item()!=null)
	{   
  		curr_user_dirs= new Enumerator(users.item().SubFolders);

      profile_exist=false;

      if(
         (users.item().Name=="Skip me")||
         (users.item().Name=="Skip me too")
         ){users.moveNext(); continue;}

     WScript.StdOut.Writeline("Scaning "+users.item().Name);
     WScript.StdOut.Writeline();
//     try{
      while(curr_user_dirs.item()!=null)
      {    
           for(i=0;i<target_dirs.length;i++)
           {
			  
  	          if(curr_user_dirs.item().Name==target_dirs[i])
              {
                 WScript.StdOut.Write("Target: "+target_dirs[i])

          	     profile_exist=true;
          	     try{
	          	     prof_size=curr_user_dirs.item().Size/mb;
    	      	     prof_size=Math.round(prof_size);

        	  	     WScript.StdOut.Write("\t\t "+prof_size+" "+" "+"("+critical_size+")");

          		     if(prof_size>critical_size)
                	 {
          	    		 str_message="Ahtung";
	          	     	 WScript.StdOut.Writeline("\t Ahtung!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" /*curr_user_dirs.item().Name+" Detected! "+"size is "+prof_size+" "+str_message+" \n"*/);
    	      	     	 users_out[cntr++]=create_obj(users.item().Name,curr_user_dirs.item().Name,prof_size);
					 

        	  	     }else WScript.StdOut.Writeline();
          	     }//try
                 catch(e)
				 {
					 WScript.StdOut.Write(" Исключение при обработке "+users.item().Name+" "+e.description+"\n");
					 access_error_users+=users.item().Name+": "+curr_user_dirs.item().Name+"\n";
				 }


              }//if
            }//for

        curr_user_dirs.moveNext();
      }//while
//     }//try
/*     catch(e)
	 {
		 WScript.StdOut.Write(" Исключение при обработке "+users.item().Name+" "+e.description+"\n");
		 access_error_users+=users.item().Name+": "+curr_user_dirs.item().Name+"\n";
	 }
*/
      if(profile_exist==false)
      {
      	WScript.StdOut.Writeline();
        without_profiles_users+=" "+users.item().Name;
      }
      WScript.StdOut.Writeline("=======================================================================");
      //WScript.Echo(curr_user_profile);
      users.moveNext();
   }
  return users_out;

}
//-----------------------------------------------------------------------------------------------
WScript.StdOut.Writeline("Check size of: ");
for(i=0;i<target_dirs.length;i++)
	WScript.StdOut.Writeline(target_dirs[i]);
//if("abc"=="abc")WScript.StdOut.Writeline("EQV");
//WScript.Quit();

arr=new Array(0);
arr=get_overflow_profile_users(critical_size);
arr=sort(arr);

var usr_list="";

if(arr.length)
{
	WScript.Echo(arr.length);
	var usr_info
	for(i=0;i<arr.length;i++)
	{
		usr_info= arr[i].size+" MB"+"("+arr[i].problem_dir_name+")"+" "+"maximum:"+critical_size+" MB"+"\n";
		usr_list+=i+1+") "+arr[i].size+" MB"+" "+arr[i].name+"("+arr[i].problem_dir_name+")"+"\n";
		SendMailBmail(arr[i].name,"Profile size",0,usr_info);
	}

	letter_body+="\n\n"+usr_list;
	WScript.StdOut.Writeline(letter_body);

	if(without_profiles_users!="")
	 {
		WScript.StdOut.Writeline("Profile dirs: ")
		for(i=0;i<target_dirs.length;i++)
			WScript.StdOut.Writeline(target_dirs[i]);

		WScript.StdOut.Writeline("--------Was not found for:");
		WScript.Echo(without_profiles_users);
		letter_body+="\n\n"+"Was not found for:"+without_profiles_users;
	 }
	if(access_error_users!="")
	 {
		WScript.StdOut.Writeline("********Access denied for: ")
		WScript.Echo(access_error_users);
		letter_body+="\n\n"+"Access denied for:\n"+access_error_users;
	 }

	f_letter=fso.CreateTextFile(f_letter_name, true); 
	f_letter.Write(letter_body);
    f_letter.Close();

	SendMailBmail("Soloviev","PROFILES OVF LIST",1,f_letter_name);

}
else
{
	WScript.StdOut.Writeline("All rights");
}

//дадим время проге отправить письма, затем удалим файлы
WScript.Sleep (1000);
if (fso.FileExists(f_letter_name))fso.DeleteFile(f_letter_name);
if (fso.FileExists(f_letter_tmp_name))fso.DeleteFile(f_letter_tmp_name);

