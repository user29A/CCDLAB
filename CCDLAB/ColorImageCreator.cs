using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using JPFITS;

namespace CCDLAB
{
	public partial class ColorImageCreator : Form
	{
		Form1 FORM1;
		Bitmap BITMAP;

		double[] REDDIMCLIM = new double[2];
		double[] GREENDIMCLIM = new double[2];
		double[] BLUEDIMCLIM = new double[2];

		double[] RED_IMG_MINMAX = new double[2];
		double[] GREEN_IMG_MINMAX = new double[2];
		double[] BLUE_IMG_MINMAX = new double[2];

		bool HALTUPDATE = false;

		public ColorImageCreator(Form1 form1)
		{
			InitializeComponent();

			FORM1 = form1;
			BITMAP = new Bitmap(FORM1.IMAGESET[0].Width, FORM1.IMAGESET[0].Height, PixelFormat.Format24bppRgb);			

			RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Min;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Max;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Min;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Max;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Min;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Max;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			RedMinCutOffLabel.Text = "Min Cutoff: " + RED_IMG_MINMAX[0];
			RedMaxCutOffLabel.Text = "Max Cutoff: " + RED_IMG_MINMAX[1];

			GreenMinCutOffLabel.Text = "Min Cutoff: " + GREEN_IMG_MINMAX[0];
			GreenMaxCutOffLabel.Text = "Max Cutoff: " + GREEN_IMG_MINMAX[1];

			BlueMinCutOffLabel.Text = "Min Cutoff: " + BLUE_IMG_MINMAX[0];
			BlueMaxCutOffLabel.Text = "Max Cutoff: " + BLUE_IMG_MINMAX[1];
		}

		private void ColorImageCreator_Load(object sender, EventArgs e)
		{
			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}
		
		private void RedMinScrollBar_Scroll(object sender, ScrollEventArgs e)
		{
			double val = RedMinScrollBar.Value * (REDDIMCLIM[1] - RED_IMG_MINMAX[0]) / 100 + RED_IMG_MINMAX[0];
			RedMinCutOffLabel.Text = "Min Cutoff: " + val;

			REDDIMCLIM[0] = val;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void RedMaxScrollBar_Scroll(object sender, ScrollEventArgs e)
		{
			double val = RedMaxScrollBar.Value * (RED_IMG_MINMAX[1] - REDDIMCLIM[0]) / 100 + REDDIMCLIM[0];
			RedMaxCutOffLabel.Text = "Max Cutoff: " + val;

			REDDIMCLIM[1] = val;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GreenMinScrollBar_Scroll(object sender, ScrollEventArgs e)
		{
			double val = GreenMinScrollBar.Value * (GREENDIMCLIM[1] - GREEN_IMG_MINMAX[0]) / 100 + GREEN_IMG_MINMAX[0];
			GreenMinCutOffLabel.Text = "Min Cutoff: " + val;

			GREENDIMCLIM[0] = val;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GreenMaxScrollBar_Scroll(object sender, ScrollEventArgs e)
		{
			double val = GreenMaxScrollBar.Value * (GREEN_IMG_MINMAX[1] - GREENDIMCLIM[0]) / 100 + GREENDIMCLIM[0];
			GreenMaxCutOffLabel.Text = "Max Cutoff: " + val;

			GREENDIMCLIM[1] = val;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void BlueMinScrollBar_Scroll(object sender, ScrollEventArgs e)
		{
			double val = BlueMinScrollBar.Value * (BLUEDIMCLIM[1] - BLUE_IMG_MINMAX[0]) / 100 + BLUE_IMG_MINMAX[0];
			BlueMinCutOffLabel.Text = "Min Cutoff: " + val;

			BLUEDIMCLIM[0] = val;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void BlueMaxScrollBar_Scroll(object sender, ScrollEventArgs e)
		{
			double val = BlueMaxScrollBar.Value * (BLUE_IMG_MINMAX[1] - BLUEDIMCLIM[0]) / 100 + BLUEDIMCLIM[0];
			BlueMaxCutOffLabel.Text = "Max Cutoff: " + val;

			BLUEDIMCLIM[1] = val;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}		

		private void DarkContrastChck_CheckedChanged(object sender, EventArgs e)
		{
			if (!DarkContrastChck.Checked)
				return;

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;
			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;
			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			MinStdvTextBox.Text = "0.0";
			MaxStdvTextBox.Text = "5.0";

			RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Mean - 0.0 * FORM1.IMAGESET[0].Stdv;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Mean + 5 * FORM1.IMAGESET[0].Stdv;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Mean - 0.0 * FORM1.IMAGESET[1].Stdv;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Mean + 5 * FORM1.IMAGESET[1].Stdv;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Mean - 0.0 * FORM1.IMAGESET[2].Stdv;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Mean + 5 * FORM1.IMAGESET[2].Stdv;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			RedMinCutOffLabel.Text = "Min Cutoff: " + RED_IMG_MINMAX[0];
			RedMaxCutOffLabel.Text = "Max Cutoff: " + RED_IMG_MINMAX[1];

			GreenMinCutOffLabel.Text = "Min Cutoff: " + GREEN_IMG_MINMAX[0];
			GreenMaxCutOffLabel.Text = "Max Cutoff: " + GREEN_IMG_MINMAX[1];

			BlueMinCutOffLabel.Text = "Min Cutoff: " + BLUE_IMG_MINMAX[0];
			BlueMaxCutOffLabel.Text = "Max Cutoff: " + BLUE_IMG_MINMAX[1];

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void WideContrastChck_CheckedChanged(object sender, EventArgs e)
		{
			if (!WideContrastChck.Checked)
				return;

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;
			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;
			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			MinStdvTextBox.Text = "-1.0";
			MaxStdvTextBox.Text = "2.0";

			RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Mean - 1 * FORM1.IMAGESET[0].Stdv;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Mean + 2 * FORM1.IMAGESET[0].Stdv;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Mean - 1 * FORM1.IMAGESET[1].Stdv;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Mean + 2 * FORM1.IMAGESET[1].Stdv;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Mean - 1 * FORM1.IMAGESET[2].Stdv;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Mean + 2 * FORM1.IMAGESET[2].Stdv;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			RedMinCutOffLabel.Text = "Min Cutoff: " + RED_IMG_MINMAX[0];
			RedMaxCutOffLabel.Text = "Max Cutoff: " + RED_IMG_MINMAX[1];

			GreenMinCutOffLabel.Text = "Min Cutoff: " + GREEN_IMG_MINMAX[0];
			GreenMaxCutOffLabel.Text = "Max Cutoff: " + GREEN_IMG_MINMAX[1];

			BlueMinCutOffLabel.Text = "Min Cutoff: " + BLUE_IMG_MINMAX[0];
			BlueMaxCutOffLabel.Text = "Max Cutoff: " + BLUE_IMG_MINMAX[1];

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void FullContrastChck_CheckedChanged(object sender, EventArgs e)
		{
			if (!FullContrastChck.Checked)
				return;

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;
			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;
			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			MinStdvTextBox.Text = "";
			MaxStdvTextBox.Text = "";

			RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Min;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Max;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Min;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Max;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Min;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Max;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			RedMinCutOffLabel.Text = "Min Cutoff: " + RED_IMG_MINMAX[0];
			RedMaxCutOffLabel.Text = "Max Cutoff: " + RED_IMG_MINMAX[1];

			GreenMinCutOffLabel.Text = "Min Cutoff: " + GREEN_IMG_MINMAX[0];
			GreenMaxCutOffLabel.Text = "Max Cutoff: " + GREEN_IMG_MINMAX[1];

			BlueMinCutOffLabel.Text = "Min Cutoff: " + BLUE_IMG_MINMAX[0];
			BlueMaxCutOffLabel.Text = "Max Cutoff: " + BLUE_IMG_MINMAX[1];

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void CancelBtn_Click(object sender, EventArgs e)
		{
			FORM1.ImageUpD(FORM1.IMAGESET[0].Image);
			FORM1.ImageWindow.Refresh();
			this.Close();
		}

		private unsafe Bitmap RGBBitMap()
		{
			BitmapData data = BITMAP.LockBits(new Rectangle(0, 0, FORM1.IMAGESET[0].Width, FORM1.IMAGESET[0].Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
			byte* bits = (byte*)data.Scan0.ToPointer();

			int bytesPerPixel = 3; // 3 bytes per pixel for 24 bpp rgb
			int height = data.Height;
			int width = data.Width;
			int stride = data.Stride;
			int bytesWidth = width * bytesPerPixel;
			double REDinvDImCLimRange = 255 / (REDDIMCLIM[1] - REDDIMCLIM[0]);
			double GREENinvDImCLimRange = 255 / (GREENDIMCLIM[1] - GREENDIMCLIM[0]);
			double BLUEinvDImCLimRange = 255 / (BLUEDIMCLIM[1] - BLUEDIMCLIM[0]);
			int Rscaling = -1, Gscaling = -1, Bscaling = -1;

			if (RedLinearRadioBtn.Checked)
				Rscaling = 0;
			else if (RedSqrtRadioBtn.Checked)
				Rscaling = 1;
			else if (RedSquaredRadioBtn.Checked)
				Rscaling = 2;
			else
				Rscaling = 3;

			if (GreenLinearRadioBtn.Checked)
				Gscaling = 0;
			else if (GreenSqrtRadioBtn.Checked)
				Gscaling = 1;
			else if (GreenSquaredRadioBtn.Checked)
				Gscaling = 2;
			else
				Gscaling = 3;

			if (BlueLinearRadioBtn.Checked)
				Bscaling = 0;
			else if (BlueSqrtRadioBtn.Checked)
				Bscaling = 1;
			else if (BlueSquaredRadioBtn.Checked)
				Bscaling = 2;
			else
				Bscaling = 3;


			Parallel.For(0, height, i =>
			{
				int istride = i * stride;
				int jcounter = -1;
				for (int j = 0; j < bytesWidth; j += bytesPerPixel)
				{
					jcounter++;
					double Rval = FORM1.IMAGESET[0][jcounter, i];
					double Gval = FORM1.IMAGESET[1][jcounter, i];
					double Bval = FORM1.IMAGESET[2][jcounter, i];

					switch (Rscaling)
					{
						case (1)://square root
						{
							Rval = Math.Sqrt(Rval);
							break;
						}
						case (2)://squared
						{
							Rval = Rval * Rval;
							break;
						}
						case (3)://log
						{
							Rval = Math.Log(Math.Sqrt(Rval * Rval) + 1);
							break;
						}
						default:
							break;
					}

					switch (Gscaling)
					{
						case (1)://square root
						{
							Gval = Math.Sqrt(Gval);
							break;
						}
						case (2)://squared
						{
							Gval = Gval * Gval;
							break;
						}
						case (3)://log
						{
							Gval = Math.Log(Math.Sqrt(Gval * Gval) + 1);
							break;
						}
						default:
							break;
					}

					switch (Bscaling)
					{
						case (1)://square root
						{
							Bval = Math.Sqrt(Bval);
							break;
						}
						case (2)://squared
						{
							Bval = Bval * Bval;
							break;
						}
						case (3)://log
						{
							Bval = Math.Log(Math.Sqrt(Bval * Bval) + 1);
							break;
						}
						default:
							break;
					}

					if (Rval < REDDIMCLIM[0])
						Rval = REDDIMCLIM[0];
					else if (Rval > REDDIMCLIM[1])
						Rval = REDDIMCLIM[1];
					Rval = (Rval - REDDIMCLIM[0]) * REDinvDImCLimRange;

					if (Gval < GREENDIMCLIM[0])
						Gval = GREENDIMCLIM[0];
					else if (Gval > GREENDIMCLIM[1])
						Gval = GREENDIMCLIM[1];
					Gval = (Gval - GREENDIMCLIM[0]) * GREENinvDImCLimRange;

					if (Bval < BLUEDIMCLIM[0])
						Bval = BLUEDIMCLIM[0];
					else if (Bval > BLUEDIMCLIM[1])
						Bval = BLUEDIMCLIM[1];
					Bval = (Bval - BLUEDIMCLIM[0]) * BLUEinvDImCLimRange;

					bits[istride + j + 0] = (byte)(Bval);   // blue
					bits[istride + j + 1] = (byte)(Gval); // green
					bits[istride + j + 2] = (byte)(Rval);   // red
				}
			});

			BITMAP.UnlockBits(data);
			return BITMAP;
		}

		private void ColorImageCreator_Shown(object sender, EventArgs e)
		{
			DarkContrastChck.Checked = false;
			DarkContrastChck.Checked = true;
		}

		private void SaveImageBtn_Click(object sender, EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.InitialDirectory = FORM1.IMAGESET.GetCommonDirectory();
			sfd.Filter = "JPG|*.jpeg";
			if (sfd.ShowDialog() == DialogResult.Cancel)
				return;

			BITMAP.Save(sfd.FileName, ImageFormat.Jpeg);
		}

		private void RedLinearRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!RedLinearRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Min;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Max;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void RedSqrtRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!RedSqrtRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			RED_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[0].Min) * Math.Sqrt(Math.Abs(FORM1.IMAGESET[0].Min));
			RED_IMG_MINMAX[1] = Math.Sqrt(FORM1.IMAGESET[0].Max);			

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void RedSquaredRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!RedSquaredRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			RED_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[0].Min) * Math.Pow(FORM1.IMAGESET[0].Min, 2);
			RED_IMG_MINMAX[1] = Math.Pow(FORM1.IMAGESET[0].Max, 2);			

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void RedLogRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!RedLogRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			RED_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[0].Min) * Math.Log(Math.Abs(FORM1.IMAGESET[0].Min + 1));
			RED_IMG_MINMAX[1] = Math.Log(FORM1.IMAGESET[0].Max);

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GreenLinearRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!GreenLinearRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Min;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Max;

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GreenSqrtRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!GreenSqrtRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			GREEN_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[1].Min) * Math.Sqrt(Math.Abs(FORM1.IMAGESET[1].Min));
			GREEN_IMG_MINMAX[1] = Math.Sqrt(FORM1.IMAGESET[1].Max);
			
			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GreenSquaredRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!GreenSquaredRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			GREEN_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[1].Min) * Math.Pow(FORM1.IMAGESET[1].Min, 2);
			GREEN_IMG_MINMAX[1] = Math.Pow(FORM1.IMAGESET[1].Max, 2);
			
			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GreenLogRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!GreenLogRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			GREEN_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[1].Min) * Math.Log(Math.Abs(FORM1.IMAGESET[1].Min + 1));
			GREEN_IMG_MINMAX[1] = Math.Log(FORM1.IMAGESET[1].Max);

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void BlueLinearRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!BlueLinearRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Min;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Max;

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void BlueSqrtRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!BlueSqrtRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			BLUE_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[2].Min) * Math.Sqrt(Math.Abs(FORM1.IMAGESET[2].Min));
			BLUE_IMG_MINMAX[1] = Math.Sqrt(FORM1.IMAGESET[2].Max);

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void BlueSquaredRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!BlueSquaredRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			BLUE_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[2].Min) * Math.Pow(FORM1.IMAGESET[2].Min, 2);
			BLUE_IMG_MINMAX[1] = Math.Pow(FORM1.IMAGESET[2].Max, 2);

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void BlueLogRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (!BlueLogRadioBtn.Checked)
				return;

			if (HALTUPDATE)
				return;

			BLUE_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[2].Min) * Math.Log(Math.Abs(FORM1.IMAGESET[2].Min + 1));
			BLUE_IMG_MINMAX[1] = Math.Log(FORM1.IMAGESET[2].Max);

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void MaxStdvTextBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode != Keys.Enter)
				return;

			e.SuppressKeyPress = e.Handled = true;

			if (!JPMath.IsNumeric(MaxStdvTextBox.Text) || !JPMath.IsNumeric(MinStdvTextBox.Text))
				return;

			double minstd = Convert.ToDouble(MinStdvTextBox.Text);
			double maxstd = Convert.ToDouble(MaxStdvTextBox.Text);			

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;
			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;
			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Mean + minstd * FORM1.IMAGESET[0].Stdv;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Mean + maxstd * FORM1.IMAGESET[0].Stdv;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Mean + minstd * FORM1.IMAGESET[1].Stdv;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Mean + maxstd * FORM1.IMAGESET[1].Stdv;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Mean + minstd * FORM1.IMAGESET[2].Stdv;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Mean + maxstd * FORM1.IMAGESET[2].Stdv;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			RedMinCutOffLabel.Text = "Min Cutoff: " + RED_IMG_MINMAX[0];
			RedMaxCutOffLabel.Text = "Max Cutoff: " + RED_IMG_MINMAX[1];

			GreenMinCutOffLabel.Text = "Min Cutoff: " + GREEN_IMG_MINMAX[0];
			GreenMaxCutOffLabel.Text = "Max Cutoff: " + GREEN_IMG_MINMAX[1];

			BlueMinCutOffLabel.Text = "Min Cutoff: " + BLUE_IMG_MINMAX[0];
			BlueMaxCutOffLabel.Text = "Max Cutoff: " + BLUE_IMG_MINMAX[1];

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GlobalLinearRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			/*RED_IMG_MINMAX[0] = FORM1.IMAGESET[0].Min;
			RED_IMG_MINMAX[1] = FORM1.IMAGESET[0].Max;

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			GREEN_IMG_MINMAX[0] = FORM1.IMAGESET[1].Min;
			GREEN_IMG_MINMAX[1] = FORM1.IMAGESET[1].Max;

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			BLUE_IMG_MINMAX[0] = FORM1.IMAGESET[2].Min;
			BLUE_IMG_MINMAX[1] = FORM1.IMAGESET[2].Max;

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();*/

			HALTUPDATE = true;
			RedLinearRadioBtn.Checked = true;
			GreenLinearRadioBtn.Checked = true;
			BlueLinearRadioBtn.Checked = true;
			HALTUPDATE = false;
			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GlobalSqrtRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			/*RED_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[0].Min) * Math.Sqrt(Math.Abs(FORM1.IMAGESET[0].Min));
			RED_IMG_MINMAX[1] = Math.Sqrt(FORM1.IMAGESET[0].Max);

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			GREEN_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[1].Min) * Math.Sqrt(Math.Abs(FORM1.IMAGESET[1].Min));
			GREEN_IMG_MINMAX[1] = Math.Sqrt(FORM1.IMAGESET[1].Max);

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();

			BLUE_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[2].Min) * Math.Sqrt(Math.Abs(FORM1.IMAGESET[2].Min));
			BLUE_IMG_MINMAX[1] = Math.Sqrt(FORM1.IMAGESET[2].Max);

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();*/

			HALTUPDATE = true;
			RedSqrtRadioBtn.Checked = true;
			GreenSqrtRadioBtn.Checked = true;
			BlueSqrtRadioBtn.Checked = true;
			HALTUPDATE = false;
			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GlobalSquaredRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			/*RED_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[0].Min) * Math.Pow(FORM1.IMAGESET[0].Min, 2);
			RED_IMG_MINMAX[1] = Math.Pow(FORM1.IMAGESET[0].Max, 2);

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			GREEN_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[1].Min) * Math.Pow(FORM1.IMAGESET[1].Min, 2);
			GREEN_IMG_MINMAX[1] = Math.Pow(FORM1.IMAGESET[1].Max, 2);

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			BLUE_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[2].Min) * Math.Pow(FORM1.IMAGESET[2].Min, 2);
			BLUE_IMG_MINMAX[1] = Math.Pow(FORM1.IMAGESET[2].Max, 2);

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();*/

			HALTUPDATE = true;
			RedSquaredRadioBtn.Checked = true;
			GreenSquaredRadioBtn.Checked = true;
			BlueSquaredRadioBtn.Checked = true;
			HALTUPDATE = false;
			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}

		private void GlobalLogRadioBtn_CheckedChanged(object sender, EventArgs e)
		{
			/*RED_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[0].Min) * Math.Log(Math.Abs(FORM1.IMAGESET[0].Min + 1));
			RED_IMG_MINMAX[1] = Math.Log(FORM1.IMAGESET[0].Max);

			REDDIMCLIM[0] = RED_IMG_MINMAX[0];
			REDDIMCLIM[1] = RED_IMG_MINMAX[1];

			RedMinScrollBar.Value = 0;
			RedMaxScrollBar.Value = 100;

			GREEN_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[1].Min) * Math.Log(Math.Abs(FORM1.IMAGESET[1].Min + 1));
			GREEN_IMG_MINMAX[1] = Math.Log(FORM1.IMAGESET[1].Max);

			GREENDIMCLIM[0] = GREEN_IMG_MINMAX[0];
			GREENDIMCLIM[1] = GREEN_IMG_MINMAX[1];

			GreenMinScrollBar.Value = 0;
			GreenMaxScrollBar.Value = 100;

			BLUE_IMG_MINMAX[0] = Math.Sign(FORM1.IMAGESET[2].Min) * Math.Log(Math.Abs(FORM1.IMAGESET[2].Min + 1));
			BLUE_IMG_MINMAX[1] = Math.Log(FORM1.IMAGESET[2].Max);

			BLUEDIMCLIM[0] = BLUE_IMG_MINMAX[0];
			BLUEDIMCLIM[1] = BLUE_IMG_MINMAX[1];

			BlueMinScrollBar.Value = 0;
			BlueMaxScrollBar.Value = 100;

			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();*/

			HALTUPDATE = true;
			RedLogRadioBtn.Checked = true;
			GreenLogRadioBtn.Checked = true;
			BlueLogRadioBtn.Checked = true;
			HALTUPDATE = false;
			FORM1.IMAGEBMP = RGBBitMap();
			FORM1.ImageWindow.Refresh();
		}
	}
}

