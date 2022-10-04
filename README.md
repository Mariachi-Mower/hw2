To compile this program you must use the make
all the objects files included in the makefile.
You can do this by calling "make amazon" on a command
line. In order to run the program you must call ./amazon
along with the name of a file containing the data for the
data base.
The program runs through user interaction at the command line.

To find products that contain all the terms, perform AND search
providing terms to search
format: AND (term) (term)

To find products containing any of the terms you provide, perform OR search
providing terms to search.
format: OR (term) (term)

To add a product to your cart perform ADD.
providing the name of the user adding and the hit result you want.
format: ADD (username) (hit number)

To view a cart, perform VIEWCART
providing the name of the user
format: VIEWCART (username)

To checkout a cart, perform BUYCART
providing the name of the user.
format: BUYCART (username)

To quit the program, perform quit and provide an output file.
format: QUIT (filename)