/*
	Cole Clark's Fractal Suite

	register.cpp
	Code that adds nodes from the dso to Houdini.
 */

 // Houdini never finds this dso without this included.
#include <UT/UT_String.h>

#include <UT/UT_DSOVersion.h>

#include "COP2_Mandelbrot.h"
#include "COP2_FractalMatte.h"
#include "COP2_Buddhabrot.h"

#include "register.h"

using namespace CC;

/// Installs the Fractal Generator Cop.
/// Houdini enforces this name for adding Cop2 Nodes.
void newCop2Operator(OP_OperatorTable* table)
{
	// Creates the Mandelbrot Definition
	OP_Operator* mandelbrot = new OP_Operator(
		"cc::fractal_mandelbrot", // Node Name
		"CC Fractal Mandelbrot", // Pretty Name
		COP2_Mandelbrot::myConstructor,
		&COP2_Mandelbrot::myTemplatePair,
		0,  // min inputs
		0,  // max inputs
		&COP2_Mandelbrot::myVariablePair,
		OP_FLAG_GENERATOR);

	// Creates the Fractal Matte Definition
	OP_Operator* fractalMatte = new OP_Operator(
		"cc::fractal_matte",
		"CC Fractal Matte",
		COP2_FractalMatte::myConstructor,
		&COP2_FractalMatte::myTemplatePair,
		1,
		2, // optional mask input.
		&COP2_FractalMatte::myVariablePair,
		0, // not generator
		COP2_FractalMatte::myInputLabels);


	OP_Operator* buddhabrot = new OP_Operator("cc::fractal_buddhabrot",
		"CC Fractal Buddhabrot",
		COP2_Buddhabrot::myConstructor,
		&COP2_Buddhabrot::myTemplatePair,
		0,
		2, // optional mask input.
		&COP2_Buddhabrot::myVariablePair,
		0, // not generator
		COP2_Buddhabrot::myInputLabels);

	// Add to tab path.
	UT_String menuPath{ "Fractal" };
	mandelbrot->setOpTabSubMenuPath(menuPath);
	fractalMatte->setOpTabSubMenuPath(menuPath);
	buddhabrot->setOpTabSubMenuPath(menuPath);

	// Register the nodes
	table->addOperator(mandelbrot);
	table->addOperator(fractalMatte);
	table->addOperator(buddhabrot);
}