package gui;

import java.util.ArrayList;
import java.util.List;

public class Layer {
	public byte [] rawData; //zbog headera cuvam
	public int width, height;
	public List<Pixel> pixels;
	public boolean visible, active;
	public MainCanvas parent = null;
	public int pixel_offset;

	
	public void setParent(MainCanvas p) { parent = p; }
	
	public Layer(byte [] data) {
		
		rawData = data;
		visible = true;  active = true;
		
		pixels = new ArrayList<>();
		
		pixel_offset = 0;
		pixel_offset = pixel_offset | Byte.toUnsignedInt(data[10]);
		pixel_offset = pixel_offset | Byte.toUnsignedInt(data[11]) * 256;
		pixel_offset = pixel_offset | Byte.toUnsignedInt(data[12]) * 65536;
		pixel_offset = pixel_offset | Byte.toUnsignedInt(data[13]) * 16777216;
		System.out.println();
		System.out.println("Pixel offset " + pixel_offset);
		System.out.println();
	//	System.out.printf("%02x ", Byte.toUnsignedInt(data[4194440]));
		System.out.println();
		//popravi u C++ da se salje i color header 
		//for (int i = pixel_offset - 1; i<data.length;)
		for (int i=138; i<data.length;) {
			Pixel p = new Pixel();
			p.B = data[i++];
		if (i == data.length ) break;
			p.G = data[i++];
		if (i == data.length ) break;
			p.R = data[i++];
		if (i == data.length ) break;
			p.A = data[i++];
		if (i == data.length - 1) break;
			
			pixels.add(p);
		}
	//	for(int i = 0; i < 100; i++)
	//	for(int i = 1048500; i < pixels.size(); i++)
	//	for(int i = 0; i < 100; i++) {
	//		System.out.printf("%02x ", Byte.toUnsignedInt(pixels.get(i).B));
	//		System.out.printf("%02x ", Byte.toUnsignedInt(pixels.get(i).G));
	//		System.out.printf("%02x ", Byte.toUnsignedInt(pixels.get(i).R));
	//		System.out.printf("%02x ", Byte.toUnsignedInt(pixels.get(i).A));
	//		System.out.println();
	//	}
		System.out.println();
		
		width = 0;
		width = width | Byte.toUnsignedInt(data[18]);
		width = width | Byte.toUnsignedInt(data[19]) * 256;
		width = width | Byte.toUnsignedInt(data[20]) * 65536;
		width = width | Byte.toUnsignedInt(data[21]) * 16777216;
		
		height = 0;
		height = height | Byte.toUnsignedInt(data[22]);
		height = height | Byte.toUnsignedInt(data[23]) * 256;
		height = height | Byte.toUnsignedInt(data[24]) * 65536;
		height = height | Byte.toUnsignedInt(data[25]) * 16777216;
		System.out.println(" velicina slike " + data.length);
		System.out.println("Broj pixela =  " +  pixels.size());
		System.out.println(width + "," + height);
	}
}
