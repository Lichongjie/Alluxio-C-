package r;

public class Sample2 {
    public String name;

    public static String sayHello(testObj o) {
        return "Hello, " + o.s1 + "!";
    }

    public testObj sayHello(String s1) {
        return new testObj(s1, 2);
    }
} 
