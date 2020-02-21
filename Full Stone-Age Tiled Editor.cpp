/**********|**********|**********|
Program: TT03_A2_HOSSAIN_MOHAMMAD_MUBDIUL.cpp
Course:TCP1101 Programming Fundamentals
Year: 2017/18 Trimester 1
Name: Hossain, Mohammad Mubdiul
ID: 1161303847
Email: 1161303847@student.mmu.edu.my
**********|**********|**********/
#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

void line1(int len[], char (*text)[20]); // This a function for printing the +/- signs at the top
void line2(int len[], char (*text)[20]); // this the function for printing the box numbers
void line(int len[], char (*text)[20], int s, int f, bool *tf); // this the function to show the texts, and it can be used to find text too.
int getInt(istream & is); // this function is created for input integer value without '\n' in the end. '\n' in the end is prohibited when inputting something
void stringtoChar(int tn, string a, char(*text)[20]); // I used String to input then covert the string value to 2D char by this function
void delete_text(int tn, int tn1, char (*text)[20]); // sometimes it was necessary to delete text and rearranging texts for few times. so I made a delete_text Function.
void showbox(int len[], char (*text)[20], bool *tf , string filename);//This function will print the box's

int main()
{
    //I used So many integer values from "last" variables only for making the undo part work.
    int length[80], tile_number, tile_number1, c, start, finish, word=1,count=0, temp_paste=0,dif, last_step=0, last_insert_tilenumber=0, last_insert_tilenumber1=0,last_tilenumber_delete=0, last_tilenumber1_delete=0,last_tilenumber_overwrite=0, last_tilenumber1_overwrite=0,last_tilenumber_paste=0,last_tilenumber1_paste=0,last_tilenumber_cut=0,last_tilenumber1_cut=0;
    char input_text[80][20], input, copy_clipboard[80][20],last_deleted[80][20], last_overwrite[80][20],temp_text[80][20],last_cut[80][20],last_load[80][20];
    string input1,  filename="NULL", find, input_string="", last_filename, last_load_filename;
    bool find_check[82]; //this bool variable will be needed for checking texts.
    for(int i=0;i<=80;i++) //Changing values to null for some variables
    {
        input_text[i][0]='\0';
        find_check[i]=false;
        last_deleted[i][0]='\0';
        last_overwrite[i][0]='\0';
        temp_text[i][0]='\0';
        last_cut[i][0]='\0';
        last_load[i][0]='\0';
    }
    cout<<"* ============================================ "<<endl<<endl;
    cout<<"File Name : "<<filename<<endl<<endl;
    cout<<endl<<"[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave,"<<endl<<"[C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo [Q]uit\n=>";
    while(input1[0]!='\n')
    {
        getline(cin, input1);
        input=input1[0];
      //  error=cin.fail();
      //  cin.clear();                                     // by this clear/ignore method we can eliminate the loop error
       // cin.ignore(10,'\n');
        switch(input)
        {
            case 'n':                                    //working with new file
            case 'N':

                if(input_text[0][0]==0)                  //if first text s empty we can guess that file is empty. so we can delete the previous empty file
                {
                    last_step=1;                        //We will undo step 1 which is creating new file
                    last_filename=filename;
                    cout<<endl<<"New file name ==> ";
                    getline(cin, filename);             //entering new filename

                }
                else
                {
                    cout<<"File is not empty. Do you want to delete existing File and change the file name(Y)(anykey to cancel)??"<<endl;
                    getline(cin, input1);
                    input=input1[0];
                    if(input=='y'||input=='Y')
                    {
                        last_step=1;
                        last_filename=filename;
                        for(int i=0;i<=80;i++)        //this loop is for deleting all the text at once so that new file can be empty
                        {
                            input_text[i][0]='\0';
                        }
                        cout<<endl<<"File deleted"<<endl<<"New File Name : ";
                        getline(cin, filename);
                    }
                }
                showbox(length, input_text, find_check, filename);
            break;

            case 'i': //working with insert
            case 'I':
                if(input_text[79][0]!='\0')
                {
                    cout<<"File Full"<<endl;             //if every tile is full the program will show that file full and prevent from entering any text
                }
                else
				{

					cout<<endl<<"Tile number ==> ";
					tile_number=getInt(cin);

					if(tile_number>=1&&tile_number<=80)       // this will limit the input from 1 to 80 (for array limitation and box numbers).
					{
					    last_step=2;                            // for undo purpose
					    tile_number--;
                        for(int i=0;i<tile_number;i++)         // this loop is to make sure not to enter text when left side tiles are empty
                        {
                            if(input_text[i][0]==0)
                            {
                                tile_number=i;
                                c=i;
                                c++;
                                cout<<"Please Fill Up Tile number "<<c<<" first!"<<endl; //if you choose a tile number middle of nowhere program will check for the last tile number which contains text then prompt to enter text in the next tile after that last tile
                            }
                        }
					    cout<<"Text ==> ";
					    getline(cin, input_string);
					    int size = input_string.length();
                        for(int j=0;j<=size;j++) // this is one of the most important loop to check whether We have entered a sentence contains extra white spaces. so this loop checks and remove the extra white spaces.
                        {
                            for(int i=0;i<=j;i++)
                            {
                                if(input_string[i]==' '&&input_string[i+1]==' ')
                                {
                                    input_string.erase(input_string.begin() + i);
                                }
                                else
                                if(input_string[0]==' ')
                                {
                                    input_string.erase(input_string.begin());
                                }
                                else
                                if(input_string[i]=='\0'&&input_string[i-1]==' ')
                                {
                                    input_string.erase(input_string.end()-1);
                                }
                            }
                        }
					    for(int i=0;i<input_string.length();i++) //And now we remove extra space now we have a perfect sentence. by this loop we can know how many words the sentence has
                        {
                            if(input_string[i]==' ')
                            {
                                word++;
                            }
                        }
                        tile_number1=tile_number+word; // every word is represents a array number, so we can add word with tile number then we will know what is the last words array.
						for(int n=79;n>=tile_number1;n--)                    //this whole loop is for 1 step forward for the texts so that i can insert the text in tile number started from 8th box to entered tile number
						{
							for(int j=0;j<20;j++)                           //changing texts in their respective forwarded tile number
							{
								input_text[n][j]=input_text[n-word][j]; // swapping text from left side to right side
							}
						}
						last_insert_tilenumber=tile_number+1;    //keeping track for first tile to end tile of the last word of the sentence for undo process
						last_insert_tilenumber1=tile_number1;   //
						stringtoChar(tile_number, input_string, input_text); //this function will now tack the sentence and assign the value to respected box and will rearrange the texts.
						word=1;
						input_string="";
					}
					else
					{
						cout<<"Enter Valid Number"<<endl;
					}
					showbox(length, input_text, find_check, filename);
				}
			break;

            case 'd': //working with delete text
            case 'D':
                cout<<endl<<"From Tile Number ==> ";
                tile_number=getInt(cin);
                cout<<"To Tile Number ==> ";
                tile_number1=getInt(cin);
                if(tile_number>=1&&tile_number<=80)
                {
                    last_step=3;                            //keeping track for undo
                    last_tilenumber_delete=tile_number;     //      "
                    last_tilenumber1_delete=tile_number1;   //      "
                    for(int i=tile_number-1,j=0;i<=tile_number1-1;i++,j++)
                    {
                        strcpy(last_deleted[j],input_text[i]); //coping the text value to last_deleted so undo can restore the deleted text
                    }
                    delete_text(tile_number, tile_number1,input_text); //now delete the selected tiles
                }
                else
                {
                    cout<<"Out of range"<<endl;
                }
                showbox(length, input_text, find_check, filename);

            break;

            case 'o': ////working with overwrite
            case 'O':
            {
                cout<<"Tile number ==> ";
                tile_number=getInt(cin);
                cout<<endl;
                if(tile_number>=1&&tile_number<=80)
                {
                    tile_number--;
                    if(input_text[tile_number][0]==0)   //if the selected box is empty then by this part will show that overwrite not possible
                    {
                        cout<<"Nothing to overwrite"<<endl;
                    }
                    else
                    {
                        last_step=4;        //keeping track for undo
                        cout<<"Text ==> ";
                        getline(cin, input_string);
                        int size = input_string.length();
                        for(int j=0;j<=size;j++) //removing extra whitespace
                        {
                            for(int i=0;i<=j;i++)
                            {
                                if(input_string[i]==' '&&input_string[i+1]==' ')
                                {
                                    input_string.erase(input_string.begin() + i);
                                }
                                else
                                if(input_string[0]==' ')
                                {
                                    input_string.erase(input_string.begin());
                                }
                                else
                                if(input_string[i]=='\0'&&input_string[i-1]==' ')
                                {
                                    input_string.erase(input_string.end()-1);
                                }
                            }
                        }
					    for(int i=0;i<input_string.length();i++)
                        {
                            if(input_string[i]==' ')
                            {
                                word++;
                            }
                        }
                        last_tilenumber1_overwrite=tile_number+word;// undo
                        last_tilenumber_overwrite=tile_number;
                        for(int i=tile_number, j=0;i<last_tilenumber1_overwrite;i++,j++)
                        {
                            strcpy(last_overwrite[j],input_text[i]);  //copying for undo
                        }
                        stringtoChar(tile_number, input_string, input_text); // overwriting the texts
                    }
                }
                else
                {
                    cout<<"Out of Range"<<endl;
                }
                showbox(length, input_text, find_check, filename);
            }
            break;

            case 's':
            case 'S':
                {
                    cout<<"File name (enter .txt) ==> ";
                    getline(cin, filename);
                    ofstream save(filename.c_str(), ios::out|ios::trunc); // save file
                    {
                        if(save) //checking the entered file name
                        {
                            for(int i=0;i<80;i++)
                            {
                                save<<input_text[i]<<" "; // saving the text into the save file
                            }
                            save.close();
                            cout<<"File saved"<<endl;
                            cout<<"------------------------ "<<filename<<" for reference ------------------------"<<endl<<endl;
                            for(int i=0;i<80;i++)
                            {
                                cout<<input_text[i]<<" "; // showing the texts that have been saved to file
                            }
                            cout<<endl;
                        }
                        else
                            cout<<"Failed To open file"<<endl;
                    }
                    showbox(length, input_text, find_check, filename);
                }
            break;

            case 'l':
            case 'L':
                {
                    string check; // this will check the entered filename first
                    cout<<"File name : ";
                    getline(cin, check);

                    ifstream open(check.c_str());
                    {
                        if(open) //checking the entered file name is available or not
                        {
                            last_step=7; //undo number
                            last_load_filename=filename; // saving the filename for later undo purpose
                            filename=check; // we can change the file name
                            for(int i=0;i<=80;i++)
                            {
                                strcpy(last_load[i],input_text[i]); //undo purpose saving all the previous texts before entering new texts from file
                            }
                            for(int i=0;i<80;i++)
                            {
                                input_text[i][0]=0; //clearing the boxes
                            }
                            for(int i=0;i<=80;i++)
                            {
								open>>input_text[i]; // loading texts from file
                            }
                            open.close();
                        }
                        else
                        {
                            cout<<"File "<<check<<" not found"<<endl;

                        }
                    }
                    showbox(length, input_text, find_check, filename);
                }
            break;

            case 'c':
            case 'C':
                {
                    cout<<"From tile number ==> ";
                    tile_number=getInt(cin);
                    cout<<"To tile number ==> ";
                    tile_number1=getInt(cin);
                    if(tile_number>=1&&tile_number<=80&&tile_number1>=tile_number&&tile_number1<=80) //checking range
                    {
                        dif=1;
                        dif+=tile_number1-tile_number;
                        for(int i=0;i<80;i++)
                        {
                            copy_clipboard[i][0]='\0'; // clearing clip-board
                        }
                        for(int i=tile_number-1,j=0;i<=tile_number1-1;i++,j++)
                        {
                            strcpy(copy_clipboard[j], input_text[i]); //coping to clipboard from texts
                        }
                    }
                    else
                    {
                        cout<<"Out of Range"<<endl;
                    }
                    showbox(length, input_text, find_check, filename);
                }
            break;
            case 'b':
            case 'B':
                {
                    if(copy_clipboard[0][0]==0)
                    {
                        cout<<"Clipboard Empty!"<<endl;
                    }
                    else
                    {
                        cout<<"Clipboard : "<<endl;
                        for(int i=0;i<dif;i++)
                        {
                            cout<<copy_clipboard[i]; // showing clipboard
                            cout<<" ";
                        }
                        showbox(length, input_text, find_check, filename);
                    }
                }
            break;

            case 'x':
            case 'X':
                {
                    cout<<"From tile number ==> ";
                    tile_number=getInt(cin);
                    cout<<"To tile number ==> ";
                    tile_number1=getInt(cin);
                    if(tile_number>=1&&tile_number<=80&&tile_number1>=tile_number&&tile_number1<=80)
                    {
                        last_step=6;
                        dif=1;
                        dif+=tile_number1-tile_number;
                        last_tilenumber_cut=tile_number;
                        last_tilenumber1_cut=tile_number1;
                        for(int i=tile_number-1,j=0;i<=tile_number1-1;i++,j++)//copying data for undoing
                        {
                            strcpy(last_cut[j],input_text[i]);
                        }
                        for(int i=0;i<80;i++)
                        {
                            copy_clipboard[i][0]='\0';
                        }
                        for(int i=tile_number-1,j=0;i<=tile_number1-1;i++,j++) // copying to clipboard from texts
                        {
                            strcpy(copy_clipboard[j], input_text[i]);
                        }
                        delete_text(tile_number, tile_number1, input_text); // deleting texts which is copied and rearranging texts.
                        for(int i=tile_number-1,j=0;i<=tile_number1-1;i++,j++) // copying to clipboard from texts
                        {
                            strcpy(copy_clipboard[j], last_cut[i]);
                        }
                        strcpy(copy_clipboard[0],last_cut[0]);// for some reason when delete function is used the first array of clipboard is removed. so we just lend the first word from the undo char.
                    }
                    else
                    {
                        cout<<"Out of range"<<endl;
                    }
					showbox(length, input_text, find_check, filename);
                }
            break;
            case 'p':
            case 'P':
                {
                    if(copy_clipboard[0][0]==0) // Checking clipboard if the clipboard is empty or not
                    {
                        cout<<"Clipboard Empty"<<endl;
                    }
                    else
                    {
                        cout<<"Tile number ==> ";
                        tile_number=getInt(cin);
                        if(tile_number>=1&&tile_number<=80)
                        {
                            last_step=5; // undo purpose
                            tile_number--;
                            tile_number1=tile_number+dif;
                            for(int n=79;n>=tile_number1;n--)
                            {
                                for(int j=0;j<20;j++)
                                {
                                    input_text[n][j]=input_text[n-dif][j]; //rearranging texts.
                                }
                            }
                            for(int i=tile_number,j=0;i<tile_number1;i++,j++)
                            {
                                strcpy(input_text[i],copy_clipboard[j]); //pasting the texts from clipboard
                            }
                            last_tilenumber_paste=tile_number+1; // undo
                            last_tilenumber1_paste=tile_number1; // "
                        }
                        else
                        {
                            cout<<"Enter Valid Number \a"<<endl;
                        }
                    }
                    showbox(length, input_text, find_check, filename);
                }
                break;

            case 'f':
            case 'F':
                count=0;
                cout<<"Enter text to find : ";
                getline(cin,find); // input for the text we will find
                for(int i=0;i<80;i++)
                {
                    if(find==input_text[i])     // checking for any match in the texts
                    {
                        find_check[i+1]=true; //  if any match found then bool array will remember the array number related to the text that have matched by making it true
                        count++; // counting to check if any texts have matched yet
                    }
                }
                if(count==0) // if no match found will show these error
                {
                    cout<<"No match found"<<endl;
                }
                showbox(length, input_text, find_check, filename); // here find_check will pass true value of matched text and will show a "=" next to its box
                for(int i=0;i<80;i++)
                {
                    find_check[i]=false; //resetting the value to false as we don't always want to see the box have "=" sign
                }
            break;

            case 'u':
            case 'U':
                if(last_step==1) // this is checking for new file name menu's undo options available or not
                {
                    filename=last_filename; //restoring the previous file name
                    cout<<"Filename Undo Successful"<<endl;
                    last_filename="";
                    last_step=0; // making it 0 prevent us from future error for non undoable steps
                }
                else
                if(last_step==2) // undo for insert
                {
                    delete_text(last_insert_tilenumber, last_insert_tilenumber1, input_text); // we saved the tilenumbers so we can just delete the tiles that have the inserted texts.
                    cout<<"Undo Successful"<<endl;
                    last_step=0;
                }
                else
                if(last_step==3) // undo for delete
                {
                    int last_def=1;
                    last_tilenumber_delete--;
                    last_tilenumber1_delete--;
                    last_def+=last_tilenumber1_delete-last_tilenumber_delete;
                    for(int n=79;n>=last_tilenumber1_delete;n--)
                    {
                        for(int j=0;j<20;j++)
                        {
                            input_text[n][j]=input_text[n-last_def][j]; //rearranging texts first.
                        }
                    }
                    for(int i=last_tilenumber_delete,j=0;i<=last_tilenumber1_delete;i++,j++)
                    {
                        strcpy(input_text[i],last_deleted[j]); // restring the texts that we deleted previously
                    }
                    cout<<"Undo Successful"<<endl;
                    for(int i=0;i<=80;i++)
                    {
                        cout<<last_deleted[i];
                    }
                    for(int i=0;i<=80;i++)
                    {
                        last_deleted[i][0]='\0'; //Making the undo array null so that it does not collide with new texts.
                    }
                    last_step=0;
                }
                else
                if(last_step==4) // undo for overwrite
                {
                    for(int i=last_tilenumber_overwrite, j=0;i<last_tilenumber1_overwrite;i++,j++)
                    {
                        strcpy(input_text[i],last_overwrite[j]);        // we just restore the overwrited text to its original positions
                    }
                    cout<<"Undo Successful"<<endl;
                    for(int i=0;i<=80;i++)
                    {
                        last_overwrite[i][0]='\0'; //Making the undo array null so that it does not collide with new texts.
                    }
                    last_step=0;
                }
                else
                if(last_step==5) // undo for paste
                {
                    delete_text(last_tilenumber_paste,last_tilenumber1_paste,input_text); // anything pasted will be deleted and will rearranged by this function
                    cout<<"Undo Successful"<<endl;
                    last_step=0;
                }
                else
                if(last_step==6) // Undo for cut. cut does not supposed to be undo but we need to restore some cut texts and rearrange the texts in the box
                {
                    int last_def=1;
                    last_tilenumber_cut--;
                    last_tilenumber1_cut--;
                    last_def+=last_tilenumber1_cut-last_tilenumber_cut;
                    for(int n=79;n>=last_tilenumber1_cut;n--)
                    {
                        for(int j=0;j<20;j++)
                        {
                            input_text[n][j]=input_text[n-last_def][j]; // rearranging texts
                        }
                    }
                    for(int i=last_tilenumber_cut,j=0;i<=last_tilenumber1_cut;i++,j++)
                    {
                        strcpy(input_text[i],last_cut[j]); // we save the texts that was cut back in. pretty much we are doing the pasting thing here
                    }
                    cout<<"Undo Successful"<<endl;
                    for(int i=0;i<=80;i++)
                    {
                        last_cut[i][0]='\0'; //Making the undo array null so that it does not collide with new texts.
                    }
                    last_step=0;
                }
                else
                if(last_step==7) // Undo for load
                {
                    filename=last_load_filename; // restoring filename
                    for(int i=0;i<=80;i++)
                    {
                        strcpy(input_text[i],last_load[i]); //restoring the texts before we loaded a file
                    }
                    cout<<"Undo Successful"<<endl;
                    last_load_filename="";
                    for(int i=0;i<=80;i++)
                    {
                        last_load[i][0]='\0'; //Making the undo array null so that it does not collide with new texts.
                    }

                    last_step=0;
                }
                else
                if(last_step==0)
                {
                    cout<<"Nothing To Undo"<<endl;
                }
                showbox(length, input_text, find_check, filename);
            break;

            case 'q':
            case 'Q':
                cout<<"Exiting...."; //terminating program
                return 0;
            break;

            default:
                cout<<"Out of range"<<endl;
                showbox(length, input_text, find_check, filename);
        }
    }
}

void line1(int len[], char (*text)[20])
{
    int n, i, j;
    cout<<"|----";
    for(n=0;n<=7;n++)
    {
        //len=strlen(text[n]);
        for(i=0;i<80;i++)
        {
            len[i]=strlen(text[i]);
        }
        for(j=n;j<80;j+=8) // this loop is important because it checks all the texts for a column and selects the longest text
        {
            if(len[n]<len[j])
            {
                len[n]=len[j];
            }
        }
        cout<<"+--";

        for(i=1;i<=len[n];i++) //for that particular column this loop prints "-" to fit the texts
        {
            cout<<"-";
        }
    }
    cout<<"|"<<endl;
}

void line2(int len[], char (*text)[20])
{
    int n,i,j,k;
    cout<<"|    ";
    for(n=1;n<=8;n++)
    {
        k=n-1;
        for(i=0;i<80;i++)
        {
            len[i]=strlen(text[i]);
        }
        for(j=k;j<80;j+=8)
        {
            if(len[k]<len[j])// this loop checks all the texts for a column and selects the longest text
            {
                len[k]=len[j];
            }
        }
        cout<<"|";
        for(i=0;i<=len[k];i++)
        {
            cout<<" "; //prints spaces for every column according to the longest texts size in respected column
        }
        cout<<n;
    }
    cout<<"|"<<endl;
}
void line(int len[], char (*text)[20], int s, int f, bool *tf) // we have 8 rows. 8 rows starts and ends with a fix number starting from 1 to 80. so for assigning numbers we have used s, and f for starting the box and finishing of box.
{
    int n, j,k,m, i,length_text;
    if(s>=1&&s<=9)
    {
        cout<<"| 0"<<s-1<<" |"; // if the row starts with 1 digit number then we will print this
    }
    else
    {
        cout<<"| "<<s-1<<" |"; // if the row starts with 2 digit number we will print this
    }
    for(n=s;n<=f;n++) //
    {
        k=n-1;
        m=n-s;
		length_text=strlen(text[k]);
		for(i=0;i<80;i++)
        {
            len[i]=strlen(text[i]);
        }
        for(j=m;j<80;j+=8) //checking the longest text for every respected column
        {
            if(len[m]<len[j])
            {
                len[m]=len[j];
            }
        }
        if(len[m]==length_text) //if text length matches with longest texts size we will print 1 space before printing the text
        {
            cout<<" "<<text[k];
        }
        else
        {
            length_text=len[m]-length_text; //we will check how small the text is from the longest one. then we will put extra spaces accordingly by this
            if(length_text%2!=0)
            {
                cout<<" ";
            }
            for(i=0;i<length_text/2;i++)
            {
                cout<<" ";
            }
            cout<<" "<<text[k];
            for(i=0;i<length_text/2;i++)
            {
                    cout<<" ";
            }
        }

        if(tf[k+1]==true) // This the crucial part for find a text. if the texts array number matches with the previously find_checks truth value then it will print the  side bar as "=".
        {
            cout<<" =";
        }
        else
        {
            cout<<" |";
        }
    }
    cout<<endl;
}

int getInt(istream & is) // we are inputing string value and converting it to integer value.
{
    string input;
    getline(is,input);
    istringstream iss(input);
    int i;
    if(!(iss >> i))
    {

    }
    return i;
}

void stringtoChar(int tn, string a, char (*text)[20])
{
    int i, n=0, tn_1;
    tn_1=tn;
    for(i=0;i<=a.length();i++)
    {
        if(a[i]==' ')
        {
            text[tn_1][n]='\0';
            tn_1++;
            n=0;
        }
        else
        {
            text[tn_1][n]=a[i];
            n++;
        }
    }
}
void delete_text(int t,int t1, char (*text)[20])
{
    int i,j,n, count, tn, tn1;
    tn=t;
    tn1=t1;

    tn--;
    tn1--;
    count=80-tn1;
    count--;

    for(n=1;n<=count;n++)
    {
        strcpy(text[tn],text[tn1+1]);
        tn++;
        tn1++;
    }
    count=count+tn;
    for(n=tn;n<=80;n++)
    {
        text[n][0]='\0';
    }
}
void showbox(int len[], char (*text)[20], bool *tf , string filename)
{
    cout<<endl<<"------------------------ new screen ------------------------"<<endl; // this is where all the values get printed
    cout<<endl<<"File name : "<<filename<<endl<<endl;

    line1(len, text);
    line2(len, text);
    line1(len, text);
    line(len, text,1,8,tf);
    line1(len, text);
   // if(text[8][0]==0)
    {
        line(len, text,9,16,tf);
        line1(len, text);
    }
    if(text[16][0]!=0)
    {
        line(len, text,17,24,tf);
        line1(len, text);
    }
    if(text[24][0]!=0)
    {
        line(len, text,25,32,tf);
        line1(len, text);
    }
    if(text[32][0]!=0)
    {
        line(len, text,33,40,tf);
        line1(len, text);
    }
    if(text[40][0]!=0)
    {
        line(len, text,41,48,tf);
        line1(len, text);
    }
    if(text[48][0]!=0)
    {
        line(len, text,49,56,tf);
        line1(len, text);
    }
    if(text[56][0]!=0)
    {
        line(len, text,57,64,tf);
        line1(len, text);
    }
    if(text[64][0]!=0)
    {
        line(len, text,65,72,tf);
        line1(len, text);
    }
    if(text[72][0]!=0)
    {
        line(len, text,73,80,tf);
        line1(len, text);
    }
    cout<<endl<<"[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave,"<<endl<<"[C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo [Q]uit\n=>";

}
