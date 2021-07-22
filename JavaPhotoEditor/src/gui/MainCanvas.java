package gui;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.util.List;

public class MainCanvas extends Canvas {
	public Layer layer;
	public Selection selection;
	
	public MainCanvas() {
		layer = null;
		selection = new Selection();
	}
	
	public Selection getSelection() { return selection; }
	
	public MainCanvas addRectangle(Rectangle r) {
		selection.addRectangle(r);
		return this;
	}
	
	
	//setuje se koji layer se iscrtava na canvasu
	public void setLayer(Layer newLayer) {
		if (newLayer != null) {
			layer = newLayer;
			layer.setParent(this);
			setSize(newLayer.width, newLayer.height);
			invalidate();
			repaint();

		}
	}

	@Override
	public void paint(Graphics g) {
		if (layer != null) { 
			BufferedImage img = new BufferedImage(layer.width, layer.height,
				    BufferedImage.TYPE_INT_ARGB);
			
			//System.out.println(img.getWidth() + " " + img.getHeight());
			
			int k = 0;
			List<Pixel> p = layer.pixels;
			for (int i=0; i<img.getWidth(); i++)
				for (int j=0; j<img.getHeight(); j++) {
					
					
					int rgba = 0;
					if(Byte.toUnsignedInt(p.get(k).B) > 255)
						p.get(k).B =  (byte) 255;
					if(Byte.toUnsignedInt(p.get(k).B) < 0)
						p.get(k).B = (byte) 0;
					rgba = rgba | Byte.toUnsignedInt(p.get(k).B);					
					if(Byte.toUnsignedInt(p.get(k).G) > 255)
						p.get(k).G = (byte) 255;
					if(Byte.toUnsignedInt(p.get(k).G) < 0)
					p.get(k).G = (byte) 0;
					rgba = rgba | Byte.toUnsignedInt(p.get(k).G) * 256;
					if(Byte.toUnsignedInt(p.get(k).R) > 255)
						p.get(k).R = (byte) 255;
					if(Byte.toUnsignedInt(p.get(k).R) < 0)
						p.get(k).R = (byte) 0;
					rgba = rgba | Byte.toUnsignedInt(p.get(k).R) * 65536;
					if(Byte.toUnsignedInt(p.get(k).A) > 255)
						p.get(k).A = (byte) 255;
					if(Byte.toUnsignedInt(p.get(k).A) < 0)
						p.get(k).A = (byte) 0;
					rgba = rgba | Byte.toUnsignedInt(p.get(k).A) * 16777216;
					
					//System.out.println(Byte.toUnsignedInt(p.get(k).R) + " " + Byte.toUnsignedInt(p.get(k).B) + " " + Byte.toUnsignedInt(p.get(k).G));
					k++;
					//System.out.printf("%8x ", rgba);
					
					img.setRGB(i, j, rgba);
					//System.out.printf("%8x ,", img.getRGB(i, j));
				}
			img = rotateImageByDegrees(img, 270);
			g.drawImage(img, 0, 0, null);

			//crta rectangle iz selekcije
			selection.drawSelection(this);
			
			//System.out.println(this);
		}
	}
	
	
	public BufferedImage rotateImageByDegrees(BufferedImage img, double angle) {

        double rads = Math.toRadians(angle);
        double sin = Math.abs(Math.sin(rads)), cos = Math.abs(Math.cos(rads));
        int w = img.getWidth();
        int h = img.getHeight();

        int newWidth = (int) Math.floor(w * cos + h * sin);
        int newHeight = (int) Math.floor(h * cos + w * sin);

        BufferedImage rotated = new BufferedImage(newWidth, newHeight, BufferedImage.TYPE_INT_ARGB);

        Graphics2D g2d = rotated.createGraphics();
        AffineTransform at = new AffineTransform();
        at.translate((newWidth - w) / 2, (newHeight - h) / 2);

        int x = w / 2;
        int y = h / 2;

        at.rotate(rads, x, y);
        g2d.setTransform(at);
        g2d.drawImage(img, 0, 0, this);
        g2d.setColor(Color.RED);
        g2d.drawRect(0, 0, newWidth - 1, newHeight - 1);
        g2d.dispose();
        return rotated;
    }
	
}
