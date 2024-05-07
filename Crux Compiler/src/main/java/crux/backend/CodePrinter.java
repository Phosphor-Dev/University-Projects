package crux.backend;

import java.io.PrintStream;

public class CodePrinter {
  PrintStream out;
  StringBuffer buffer = new StringBuffer();
  public CodePrinter(String name) {
    try {
      out = new PrintStream(name);
    } catch (Exception e) {
      e.printStackTrace();
      System.exit(-1);
    }
  }

  public void printLabel(String s) {
    out.println(s);
  }

  public void printCode(String s) {
    out.println("    " + s);
  }

  public void close() {
    out.close();
  }

  public void bufferCode(String s) {
    buffer.append("    " + s + "\n");
  }

  public void bufferLabel(String s) {
    buffer.append(s + "\n");
  }

  public void outputBuffer() {
    out.print(buffer);
    buffer = new StringBuffer();
  }

}