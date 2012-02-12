package org.xkit.demo.jni;

public class HelloJNI {
	private native void print();

	public static void main(String[] args) {
		new HelloJNI().print();
	}

	static {
		System.out.println(System.getProperty("java.library.path"));
		System.loadLibrary("HelloJNI");
	}
}
