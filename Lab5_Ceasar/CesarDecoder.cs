using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace Infobez_Cesar
{
    class CesarDecoder
    {
        static public string rusLeters = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
        static public double[] rusLetterFrequqncy =
            new double[] { 
                0.07298/*а*/,
                0.01592/*б*/,
                0.06333/*в*/,
                0.01587/*г*/,
                0.03577/*д*/,
                0.06383/*е*/,
                0.0145/*ж*/,
                0.02615/*з*/,
                0.07367/*и*/,
                0.01641/*й*/,
                0.03486/*к*/,
                0.04773/*л*/,
                0.04343/*м*/,
                0.067/*н*/,
                0.10983/*о*/,
                0.02804/*п*/,
                0.05446/*р*/,
                0.03203/*с*/,
                0.04368/*т*/,
                0.01208/*у*/,
                0.00267/*ф*/,
                0.02001/*х*/,
                0.00639/*ц*/,
                0.00966/*ч*/,
                0.0094/*ш*/,
                0.00361/*щ*/,
                0.00037/*ъ*/,
                0.03598/*ы*/,
                0.00718/*ь*/,
                0.00331/*э*/,
                0.00486/*ю*/,
                0.01735/*я*/
            };
        static public string engLetters = "abcdefghijklmnopqrstuvwxyz";
        static public double[] engLettersFrequency =
             new double[]{
                0.0609, /*a*/
                0.0149, /*b*/
                0.0425, /*c*/
                0.0403, /*d*/
                0.127, /*e*/
                0.0276, /*f*/
                0.0197, /*g*/
                0.0599, /*h*/
                0.08, /*i*/
                0.0014, /*j*/
                0.0015, /*k*/
                0.0278, /*l*/
                0.0202, /*m*/
                0.0633, /*n*/
                0.075, /*o*/
                0.0241, /*p*/
                0.001, /*q*/
                0.0697, /*r*/
                0.0675, /*s*/
                0.09, /*t*/
                0.0236, /*u*/
                0.0098, /*v*/
                0.0193, /*w*/
                0.0077, /*x*/
                0.0223, /*y*/
                0.0005 /*z*/
            };
        //new double[]{
        //    0.08,/*a*/
        //    0.0149,/*b*/
        //    0.0278,/*c*/
        //    0.0425,/*d*/
        //    0.127,/*e*/
        //    0.0223,/*f*/
        //    0.0202,/*g*/
        //    0.0609,/*h*/
        //    0.0697,/*i*/
        //    0.0014,/*j*/
        //    0.0077,/*k*/
        //    0.0403,/*l*/
        //    0.0241,/*m*/
        //    0.0675,/*n*/
        //    0.075,/*o*/
        //    0.0193,/*p*/
        //    0.001,/*q*/
        //    0.0599,/*r*/
        //    0.0633 ,/*s*/
        //    0.09,/*t*/
        //    0.0276,/*u*/
        //    0.0098,/*v*/
        //    0.0236,/*w*/
        //    0.0015,/*x*/
        //    0.0197,/*y*/
        //    0.0005/*z*/
        //};

        public static void init()
        {
            rusLetterFrequqncy = new double[rusLeters.Length];
            Random rnd = new Random(DateTime.Now.Millisecond);
            for (int i = 0; i < rusLetterFrequqncy.Length; ++i)
                rusLetterFrequqncy[i] = rnd.Next(10, 1000) * .001;
        }
        public CesarDecoder()
        {

        }

        private double[] calculateFrequency(string mess, string alphabet)
        {
            double[] res = new double[alphabet.Length];
            int leng = 0;
            foreach (char c in mess)
            {
                int ind = alphabet.IndexOf(c);
                if (ind < 0)
                    continue;
                leng++;
                res[ind] += 1.0;
            }
            for (int i = 0; i < res.Length; ++i)
                res[i] /= (double)(mess.Length);

            return res;
        }

        public string reportFreq(double[] freq, string alphabet, double[] baseFreq)
        {
            if (freq.Length != alphabet.Length)
                return "incorrect letter count! (" + freq.Length + "!=32)";

            string res = "";
            for (int i = 0; i < alphabet.Length; ++i)
                res += alphabet[i] + " :  " + baseFreq[i] + "%\r\n";
            return res;
        }

        private string transformString(double[] hasFreq, double[] baseFreq, string alphabet)
        {
            string debugMessage = "";
            int size = alphabet.Length;
            bool[] usedBase = new bool[size];
            bool[] usedHas = new bool[size];
            char[] res = new char[size];
            for (int i = 0; i < size; ++i)
            {
                usedBase[i] = false;
                usedHas[i] = false;
            }
            for (int i = 0; i < size; ++i)
            {
                double maxFreqHas = -1, maxFreqBase = -1;
                int bestIndHas = -1, bestIndBase = -1;

                for (int j = 0; j < size; ++j)
                {
                    if (!usedHas[j] && maxFreqHas < hasFreq[j]) { bestIndHas = j; maxFreqHas = hasFreq[j]; }
                    if (!usedBase[j] && maxFreqBase < baseFreq[j]) { bestIndBase = j; maxFreqBase = baseFreq[j]; }
                }
                // changes
                res[bestIndHas] = alphabet[bestIndBase];
                usedHas[bestIndHas] = true;
                usedBase[bestIndBase] = true;
                debugMessage += alphabet[bestIndHas] + " = " + alphabet[bestIndBase] + " -- \t" + maxFreqHas + "\t/\t" + maxFreqBase + "\r\n";
            }
            string resStr = "";
            foreach (char c in res)
                resStr += c;

            // jptkmdcbxwqunvlfaygrzehios
            //MessageBox.Show(debugMessage);
            return resStr;
        }

        private string decodeByReplace(string message, string was, string become)
        {
            string res = "";
            foreach (char c in message)
                if (was.IndexOf(c) < 0)
                    res += c;
                else
                    res += become[was.IndexOf(c)];
            return res;
        }

        public string Decode(string incomeMessage, string letterAlphabet, double[] letterFreq)
        {
            double[] freq = calculateFrequency(incomeMessage, letterAlphabet);

            string key = transformString(freq, letterFreq, letterAlphabet);

            //return key;// 
            return decodeByReplace(incomeMessage, letterAlphabet, key);
        }

        public string InteractiveDecode(string incomeMessage, string letterAlphabet, double[] letterFreq)
        {
            //string[] approaching = "в прежние годы охотный ряд был застроен с одной стороны старинными домами, а с другой - длинным".Split(' ');
            string[] approaching = "for example, if a patent license would not permit royalty-free redistrubution of the program by".Split(' ');
            string alphabet = letterAlphabet, key0 = alphabet;
            double[] baseFreq = letterFreq;

            double[] freq = calculateFrequency(incomeMessage, alphabet);
            string[] words = incomeMessage.Split(' ');
            int j = 0;
            foreach (string word in words)
            {
                ++j;
                string key = key0 = transformString(freq, baseFreq, alphabet);
                string res = decodeByReplace(word + "", alphabet, key);

                string change = j <= approaching.Length ? approaching[j - 1] : res;
                //char change = Interaction.InputBox("Translating '" + word + "' -> '" + res + "'. Are you sure it is correct?", "User correctence", res)[0];
                //MessageBox.Show(change + "___" + res[0]);
                if (change == res || change.Length != res.Length)
                    continue;
                for (int i = 0; i < change.Length; ++i)
                {
                    int i1 = alphabet.IndexOf(res[i]);
                    int i2 = alphabet.IndexOf(change[i]);
                    if (i1 < 0 || i2 < 0)
                        continue;
                    double tmp = baseFreq[i1];
                    baseFreq[i1] = baseFreq[i2];
                    baseFreq[i2] = tmp;
                }
            }
            return decodeByReplace(incomeMessage, alphabet, key0);
        }
        public string InteractiveByLetterDecode(string incomeMessage, string letterAlphabet, double[] letterFreq)
        {
            //string approaching = "в прежние годы охотный ряд был застроен с одной стороны старинными домами, а с другой - длинным";
            string approaching = "for example, if a patent license would not permit royalty-free redistrubution of the program by";
            string alphabet = letterAlphabet, key0 = alphabet;
            double[] baseFreq = letterFreq;

            double[] freq = calculateFrequency(incomeMessage, alphabet);
            int j = 0;
            foreach (char word in incomeMessage)
            {
                ++j;
                if (j > approaching.Length) break;
                string key = key0 = transformString(freq, baseFreq, alphabet);
                char res = decodeByReplace(word + "", alphabet, key)[0];

                char change = j <= approaching.Length ? approaching[j - 1] : res;
                if (change == res)
                    continue;

                int i1 = alphabet.IndexOf(res);
                int i2 = alphabet.IndexOf(change);
                if (i1 < 0 || i2 < 0)
                    continue;
                double tmp = baseFreq[i1];
                baseFreq[i1] = baseFreq[i2];
                baseFreq[i2] = tmp;

            }
            //return key0;
            string r = "{\r\n";
            for (int i = 0; i < baseFreq.Length; ++i)
                r += Math.Round(10000 * baseFreq[i]) / 10000 + ", /*" + letterAlphabet[i] + "*/\r\n";

            return r + "} " + transformString(freq, baseFreq, alphabet) + " -> " + alphabet; //
            return decodeByReplace(incomeMessage, alphabet, key0);
        }

    }
}
