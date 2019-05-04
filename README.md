<h1>Condensed Tree display for students</h1>

<p>This file was created as an educational tool to display
basic Binary Trees in a more human readable form. I created
this file in the hope that students new to the concept of trees
would see their own implemented Binary Trees displayed on the
output console, thus simplifying the debugging process a bit.</p>
<p><strong><i>Note</i></strong>:	This code produces a "condensed" display of the tree.
  Be careful when working out tree's Top and Bottom views
  using this display!</p>
      
      
<h2>USAGE DETAILS:</h2>

<p>This header defines a functor 'shoTree' template which takes
your tree's node type as a template parameter and the root node as the
function parameter.</p>

e.g.	First, include this header:

			#include "shoTree"

Then, make an object of shoTree template :

			shoTree<Tnode>	treeDisp;

where, Tnode is the node type used by your Binary Tree
<p><strong><i>Note</i></strong>: Your tree node <b>MUST</b> use 'data', 'left' and 'right'
			fields ,otherwise you'll have to do a search and replace
			in this header, carefully avoiding std::left
			and std::right</p>

Now, use this object as a funtion to display the tree:

			treeDisp(root);

<p>This call must be made by a tree class member, since
most likely, the root node will be a private member
Not to mention, 'root' must be of type (Tnode *)</p>

<h2>COMPATIBILTY:</h2>
<h3>64bit</h3>
			<p>Using the support of multi-byte characters, box drawing
			characters can be used for
			_shoTreeDash, _shoTreeLchild and _shoTreeRchild
			to get a prettier display, add this compiler option with a 64bit
			version of g++:</p>

			-fexec-charset=cp437
			
			<p>Get 64bit gcc for Windows here:
				<a href=https://mingw-w64.org/doku.php/download/mingw-builds>mingw-w64</a>
			</p>
<h3>32bit</h3>
			<p>Lack of multi-byte characters leaves only '-', '/', '\\'
			fit for the job...
			Comment out the box drawing #defines and uncomment the
			ones using dashes and slashes. No extra compiler options needed.</p>

<h2>Other data types:</h2>
				<p>int , char , string		types are supported by default.
  			If your tree stores data types other than int, char and string,
  			then you would need to define two functions for the data type
  			in global scope or class shoTree:</p>

  			int width(DType data);
  			{
  				Returns the length of data in no. of characters as
  				printed on console
  			}
			std::ostream& operator<<(std::ostream& cout,DType data)
			{
 				Prints the data on console without any newlines
			}
