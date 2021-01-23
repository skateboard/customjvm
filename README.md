<h1 align="center">CustomJVM</h1>
<div align="center">
<strong> A customjvm made for java!</strong>
</div>
<br />

# Introduction
This is a simple C++ program that creates a JVM inside the program. It finds a class called ```Start``` and calls main(String[]) static void!

# Start Class Example
You have to create a custom start class like this example for minecraft
```java

public class Start {
    public static void main(String[] args) {
        final String applicationData = System.getenv("APPDATA");
        final File workingDirectory = new File(applicationData, ".minecraft/");
        Main.main(new String[] { "--version", "1.8.9", "--accessToken", "0", "--assetIndex", "1.8", "--userProperties", "{}", "--gameDir", new File(workingDirectory, ".").getAbsolutePath(), "--assetsDir", new File(workingDirectory, "assets/").getAbsolutePath()});
    }
}
```
