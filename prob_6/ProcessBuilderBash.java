package prob_6;

import java.io.*;
import java.util.Scanner;

public class ProcessBuilderBash {

    public static void main(String[] args) throws IOException, InterruptedException {

        // handling for cd seperately as this does not work

        try (Scanner input = new Scanner(System.in)) {
            System.out.println("Enter command");

            String string = input.nextLine();
            args = string.split("[ \t\n]+");
        }

        if (args[0].equals("cd")) {
            cdProcess(args);
        }
        else {
            ProcessBuilder processBuilder = new ProcessBuilder(args);

            try {

                Process process = processBuilder.start();

                BufferedReader reader =
                        new BufferedReader(new InputStreamReader(process.getInputStream()));

                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }

                int exitCode = process.waitFor();
                System.out.println("\nExited with error code : " + exitCode);

            } catch (IOException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }

    public static void cdProcess (String[] command) throws IOException, InterruptedException {

        /* cd does not change directory because the File path sent in pb.directory(file)
            line does not produce actual path for cd to execute. I tried debugging and researching
            but could not find a way to resolve... an interesting problem
            This comment on StackOverflow clarifies: https://stackoverflow.com/a/4884715
        */

        String directory = System.getProperty("user.dir");
        ProcessBuilder pb = new ProcessBuilder(directory);
        File file = new File(directory);
        
        if (command.length > 2) {
            System.err.print("Syntax Error\n");
            return;
        }

        else if (command.length == 1 || command[1].equals("/")) {
            directory = System.getProperty("user.dir");
            file = new File(directory);
            pb.directory(file);
          }

          else if (command[1].equals("..")) {
            file = new File(directory);
            directory = file.getParent();
            pb.directory(file);
          }
          //error for trying to put cd as a background process
          else if (command[1].equals("&")) {
            return;
          }
          // sets the directory to the new directory if it exists.
          else {
            String userDir = command[1];
            file = new File(userDir);
            if (file.exists() == true) {
              directory = file.getCanonicalPath();
              pb.directory(file);
            }
            else if (file.exists() == false) {
              System.err.print("Invalid directory " + command[1] + "\n");
              return;
            }
        }

        Process process = pb.command(command).start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        int exitCode = process.waitFor();
        System.out.println("\nExited with error code : " + exitCode);
    }

}
