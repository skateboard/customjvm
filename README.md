<h1 align="center">CustomJVM</h1>
<div align="center">
<strong> A customjvm made for minecraft!</strong>
</div>
<br />

# Introduction
This is a very simple c++ program that creates a custom JVM. It finds the start class and calls the main(String[]) static void.

This was made for minecraft but can be used for other java programs.

# Start Class Example
You have to create a custom start class like this example for minecraft
```java

public class Start
{
    public static void main(String[] args) {
        final String applicationData = System.getenv("APPDATA");
        final File workingDirectory = new File(applicationData, ".minecraft/");
        Main.main(new String[] { "--version", "1.8.9", "--accessToken", "0", "--assetIndex", "1.8", "--userProperties", "{}", "--gameDir", new File(workingDirectory, ".").getAbsolutePath(), "--assetsDir", new File(workingDirectory, "assets/").getAbsolutePath() });
    }
}
```
