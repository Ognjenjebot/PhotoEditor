package gui;

import java.awt.Canvas;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;

import gui.Pixel;

public class Image extends Canvas {
	public ArrayList<Layer> layers = new ArrayList<Layer>(); 
	
	@Override
	public void paint(Graphics arg0) {

	}
	
	public native byte [] loadBMPImage(String pathToImage);
	public native boolean exportBMPImage(byte[] headersandpixels, String Path);
	
	public void drawBMPImage(String pathToImage, MainCanvas canvas) {
		System.loadLibrary("C++PhotoEditor");
		System.out.println(pathToImage);
		byte [] result = loadBMPImage(pathToImage);
	//	System.out.println(result.length);
		//for (int i=0; i<250; i++) {
		//	System.out.printf("%02x ", Byte.toUnsignedInt(result[i]));
		//	if (i != 0 && i % 16 == 0) System.out.println("");
		//}
		
		Layer l = new Layer(result);
		if(layers.isEmpty()) {
			canvas.setLayer(l);

		}
		layers.add(l);

		//LayerCheck
		//Na canvasu setujemo koji layer hocemo da iscrtamo, a mozemo i da spojimo vise njih?
		//na samom kraju liste ce biti merged layer, pa ako se posle korisnik odluci da neki sloj ne bue visible, izbrisace se merged layer i scrtace se onaj koji treba
		
		
	
	}

	public void exportImage(String path) {
		// for (int i=138; i<data.length;) {
		
		for (int i = 138 , j = 0; i<layers.get(0).rawData.length; j++) {
		layers.get(0).rawData[i++] = layers.get(0).pixels.get(j).B;
	if (i == layers.get(0).rawData.length ) break;
		layers.get(0).rawData[i++] = layers.get(0).pixels.get(j).G;
	if (i == layers.get(0).rawData.length ) break;
		layers.get(0).rawData[i++] = layers.get(0).pixels.get(j).R;
	if (i == layers.get(0).rawData.length ) break;
		layers.get(0).rawData[i++] = layers.get(0).pixels.get(j).A;
	if (i == layers.get(0).rawData.length - 1) break;
		}
		
		System.out.println(path);
		System.out.printf("%02x ", Byte.toUnsignedInt(layers.get(0).rawData[138]));

		exportBMPImage(layers.get(0).rawData, path); 
		
	}
	
	public void mergeLayers() {
		//spajanje slojeva
		
//		  std::vector<Pixel> Image::flattenLayers()       //sve layere pretvara u jedan, tj samo piksele, ostali podaci ce biti isti kao kod layer[0]
	
			float tmpA, tmp;
			float sumA, sumB, sumG, sumR;
//
			 List<Pixel> pom;
			 pom = new ArrayList<>();
			 //Byte.toUnsignedInt(layers.get(0).pixels.get(i).A)
			for (int i = 0; i < layers.get(0).height * layers.get(0).width; i++) {

				tmpA =  (float) ((1 - Byte.toUnsignedInt(layers.get(0).pixels.get(i).A) / 255.0) * (Byte.toUnsignedInt(layers.get(1).pixels.get(i).A) / 255.0));
			//	System.out.println();
			//	System.out.println("tmpA je  ------>" + tmpA);
			//	System.out.println("pixelA  layer 0 je  ------>" + Byte.toUnsignedInt(layers.get(0).pixels.get(i).A));
			//	System.out.println("pixelA  layer 1 je  ------>" + Byte.toUnsignedInt(layers.get(1).pixels.get(i).A));
				sumA = (float) ((Byte.toUnsignedInt(layers.get(0).pixels.get(i).A) / 255.0) + tmpA);
				if (sumA != 0) {
					for (int j = 2; j < layers.size(); j++) {
						tmpA = (float) (tmpA * (layers.get(j).pixels.get(i).A / 255.0));
						sumA += tmpA;
					}
					
					tmp = (float) ((1 - (Byte.toUnsignedInt(layers.get(0).pixels.get(i).A) / 255.0)) * (Byte.toUnsignedInt(layers.get(1).pixels.get(i).A) / 255.0) / sumA);
					sumR = (float) (Byte.toUnsignedInt(layers.get(0).pixels.get(i).R) * (Byte.toUnsignedInt(layers.get(0).pixels.get(i).A) / 255.0) / sumA + Byte.toUnsignedInt(layers.get(1).pixels.get(i).R) * tmp);
					sumG = (float) (Byte.toUnsignedInt(layers.get(0).pixels.get(i).G) * (Byte.toUnsignedInt(layers.get(0).pixels.get(i).A) / 255.0) / sumA + Byte.toUnsignedInt(layers.get(1).pixels.get(i).G) * tmp);
					sumB = (float) (Byte.toUnsignedInt(layers.get(0).pixels.get(i).B) * (Byte.toUnsignedInt(layers.get(0).pixels.get(i).A) / 255.0) / sumA + Byte.toUnsignedInt(layers.get(1).pixels.get(i).B) * tmp);
					for (int j = 2; j < layers.size(); j++) {
						tmp *= (layers.get(j).pixels.get(i).A / 255.0);
						sumR = sumR + tmp * Byte.toUnsignedInt(layers.get(j).pixels.get(i).R);
						sumG = sumG + tmp * Byte.toUnsignedInt(layers.get(j).pixels.get(i).G);
						sumB = sumB + tmp * Byte.toUnsignedInt(layers.get(j).pixels.get(i).B);
					}
//					//napravi pixel sa vrednostima sumA, sumB, sumG, sumR
					pom.add(new Pixel((byte)sumB, (byte)sumG, (byte)sumR, (byte)(sumA * 255.0)));
				}
				else
					pom.add(new Pixel((byte)255, (byte)255, (byte)255, (byte)0));
			}
			
			for (int i = 0; i < layers.get(0).pixels.size(); i++) {
				layers.get(0).pixels.get(i).B = pom.get(i).B;
				layers.get(0).pixels.get(i).G = pom.get(i).G;
				layers.get(0).pixels.get(i).R = pom.get(i).R;
				layers.get(0).pixels.get(i).A = pom.get(i).A;
			}
			
			for(int i = 0; i < 100; i++) {
				System.out.printf("%02x ", Byte.toUnsignedInt(pom.get(i).B));
				System.out.printf("%02x ", Byte.toUnsignedInt(pom.get(i).G));
				System.out.printf("%02x ", Byte.toUnsignedInt(pom.get(i).R));
				System.out.printf("%02x ", Byte.toUnsignedInt(pom.get(i).A));
				System.out.println();
			}
		}

	public void addTransparency(int t) {
		float transparency =  (float) (t / 100.0);
		
		for(Layer l : layers) {
			for(int i = 0; i < l.pixels.size(); i++) {				
				float c = Byte.toUnsignedInt(l.pixels.get(i).A) * transparency;
				byte d = (byte) c;
				l.pixels.get(i).A = d;
				//l.pixels.get(i).A *= transparency;
			//	l.pixels.get(i).A = (byte) ((int)((float)l.pixels.get(i).A * transparency-128.0));
							
			}
		}
		
	}
	
}