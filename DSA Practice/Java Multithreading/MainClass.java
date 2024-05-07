import java.lang.String;
import java.util.*;
import java.io.*;

class Disk{//NEEDED
    // extends Thread
    static final int NUM_SECTORS = 2048;
    StringBuffer sectors[] = new StringBuffer[NUM_SECTORS];
    
    Disk(){

    }

    void write(int sector, StringBuffer data){// call sleep
    
    }
    void read(int sector, StringBuffer data){  // call sleep
    
    }
}

class Printer{//NEEDED
    // extends Thread
    Printer(int id){}
    //new FileWriter(fileName, true);

    void print(StringBuffer data){} // call sleep
}

class PrintJobThread extends Thread{//NEEDED
    StringBuffer line = new StringBuffer(); // only allowed one line to reuse for read from disk and print to printer

    PrintJobThread(String fileToPrint){}

    @Override
    public void run(){}
}

class FileInfo{//NEEDED
    int diskNumber;
    int startingSector;
    int fileLength;
}

class DirectoryManager{//NEEDED
    private Hashtable<String, FileInfo> T = new Hashtable<String, FileInfo>();

    DirectoryManager(){}

    void enter(StringBuffer fileName, FileInfo file){}

    FileInfo lookup(StringBuffer fileName){
        return null;
    }
}

class ResourceManager{
    boolean isFree[];
	ResourceManager(int numberOfItems){
		isFree = new boolean[numberOfItems];
		for (int i=0; i<isFree.length; ++i)
			isFree[i] = true;
	}

	synchronized int request(){
		while (true){
			for (int i = 0; i < isFree.length; ++i)
				if (isFree[i]) {
					isFree[i] = false;
					return i;
                }
            //this.wait(); // block until someone releases Resource
        }
    }

    synchronized void release(int index){
            isFree[index] = true;
            this.notify(); // let a blocked thread run
        }
}

class DiskManager{
}

class PrinterManager{//NEEDED
}

class UserThread extends Thread{//NEEDED
    String fileName;
	String line;
    UserThread(int id){ // my commands come from an input file with name USERi where i is my user id
        this.fileName = "USER0";
        System.out.println(this.fileName);
    }

    @Override
    public void run() {
        try{
            FileWriter myWriter = new FileWriter("PRINTER0");//TEMP
            
            FileInputStream inputStream = new FileInputStream("USER0");
            BufferedReader myReader = new BufferedReader(new InputStreamReader(inputStream));
            
            String command, name;

            boolean diskAccess = false;//TEMP
            String tempArr[] = new String[5];//TEMP
            int counter = 0;
            for (String line; (line = myReader.readLine()) != null; )
            {   


                StringTokenizer iterator = new StringTokenizer(line, " ");
                List<String> tokens = new ArrayList<String>();
                while (iterator.hasMoreTokens()) {
                    tokens.add(iterator.nextToken());
                }
                command = tokens.get(0);
                if (command.equals(".save")){
                    name = tokens.get(1);
                    diskAccess = true;


                    //System.out.println(".save");
                } else if(command.equals(".end")){
                    diskAccess = false;
                    counter = 0;

                    //System.out.println(".end");

                } else if(command.equals(".print")){
                    name = tokens.get(1);
                        for (int i = 0; i < tempArr.length; i++){
                            myWriter.write(tempArr[i]);
                            myWriter.write("\n");
                    }

                    //System.out.println(".print");
                } else {
                    if (diskAccess == true){
                        System.out.println(line);
                        tempArr[counter] = line;
                        counter++;
                    }
                    //System.out.println(".content");
                }
                
            }
            myWriter.close();
            inputStream.close();
            
        }catch (Exception e) {e.printStackTrace();}
    }
}



public class MainClass{
    private static MainClass osObject;
    int NUM_USERS, NUM_DISKS, NUM_PRINTERS;
    UserThread users[];
    Disk disks[];
    Printer printers[];
    DiskManager diskManager;
    PrinterManager printerManager;

    private MainClass(){}
    void configure(String argv[]){
    // parse args and assign values to parameters
        NUM_USERS = Integer.parseInt(argv[0].substring(1));
        NUM_DISKS = Integer.parseInt(argv[1].substring(1));
        NUM_PRINTERS = Integer.parseInt(argv[2].substring(1));
    }

    static MainClass getInstance(){
        if (osObject == null)
            osObject = new MainClass();
        return osObject;
    }
    
    void startUsers(){
        for(int i = 0; i < NUM_USERS; i++)
		    users[i].run();
    }

    void joinUsers(){}

    public static void main(String args[]){
        MainClass os = MainClass.getInstance();
        os.configure(args);
        System.out.println("USERS: " + os.NUM_USERS);
        System.out.println("DISKS: " + os.NUM_DISKS);
        System.out.println("PRINTERS: " + os.NUM_PRINTERS);
        

        os.users = new UserThread[os.NUM_USERS];
        for(int i = 0; i < os.NUM_USERS; i++){
            os.users[i] = new UserThread(i);
        }

        /*os.disks = new Disk[os.NUM_DISKS];
        for(int i = 0; i < os.NUM_USERS; i++){
            os.disks[i] = new = Disk(i);
        }*/

        os.printers = new Printer[os.NUM_PRINTERS]; 
        for(int i = 0; i < os.NUM_USERS; i++){
            os.printers[i] = new Printer(i);
        }

        //os.diskManager = new DiskManager();
        //os.printerManager = new PrinterManager();

        os.startUsers();
        os.joinUsers();
        System.out.println("*** 141 OS Simulation ***");
    }
}
