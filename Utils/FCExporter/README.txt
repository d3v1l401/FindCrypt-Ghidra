The following libraries are now required to compile this exporter project:

	- Crypto++ (GZip)
	
Quick description:

	- FCExporter
		Exporter util for native constants directly into the database,
		can compress the buffers and build the database without aid of
		human intervention.
		
		The content of the database is just the name of the algorithm
		and its binary constants content.
		
		
		
	- FCTreeExporter
		Exporter util for native constants directly into the database,
		can compress the buffers and builds the database comprise with
		masks for dynamic constants (e.g. code signature) automatically
		compressed; without the aid of the human intervention.
		
		This database is used only for particular signature scanning 
		phases and it's slightly more complex to understand.
		Highly recommended to read and understand the structure and the 
		logic of signature scanning with masks.
		
	
	Reference to GitHub Wiki to better understand database structures 
	and logic behind such decisions.