package org.xkit.demo.jni;

public class HelloJNI {

	private native boolean initNative();

	private native void print();

	private native void print(String msg);

	private native String echo(int times, String msg);

	private native int[] draw(int[] data);

	private native void call();

	public void vmSayHello(String greeting) {
		System.out.println(greeting);
	}

	public static void main(String[] args) {
		HelloJNI jni = new HelloJNI();
		
		jni.print();
		jni.print("Hello, I'm from Java layer");
		jni.print("你好，我来自Java层");

		System.out.println(jni.echo(2, "am i low case?"));

		int[] data = { 7, 4, 5, 63, 3 };
		data = jni.draw(data);

		printArray(data);
		jni.initNative();
		jni.call();
	}

	static {
		System.out.println(System.getProperty("java.library.path"));
		System.loadLibrary("HelloJNI");
	}

	private static void printArray(int[] ia) {
		StringBuilder buffer = new StringBuilder();
		for (int i = 0, l = ia.length; i < l; i++) {
			buffer.append(ia[i] + " ");
		}
		buffer.deleteCharAt(buffer.length() - 1);
		System.out.println(buffer);
	}
}
