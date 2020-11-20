/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
//#include "regionProperties.H"

int main(int argc, char *argv[])
{
	timeSelector::addOptions();

    argList::addNote
    (
		"Input argument is field of alpha\n"
        "Optional argument is a name from the list of regions from constant/regionProperties"
    );

	argList::validArgs.append("field");

	argList::noParallel();
	argList::addOption
	(
		"region",
		"word"
	);
	word myRegion = "empty";
    #include "setRootCase.H"
	// These two create the time system (instance called runTime) and fvMesh (instance called mesh).
    #include "createTime.H"
	instantList timeDirs = timeSelector::select0(runTime, args);
	#include "createMesh.H"

	// It creates mesh if the parameter "region" is used
	if (args.found("region") )
	{
		args.readIfPresent("region", myRegion);
		fvMesh mesh
		(
    		Foam::IOobject
    		(
    		    myRegion,
    		    runTime.timeName(),
    		    runTime,
    		    IOobject::MUST_READ
    		)

		);
		Info << "Region name: " << myRegion << nl << endl;
	}

	// read field name
	const word field = args[1];

	// creates outputFile
	fileName outputDir = mesh.time().path()/"postProcessing";
	mkDir(outputDir);
	autoPtr<OFstream> outputFilePtr;
	word	fieldName= field + ".dat";
	outputFilePtr.reset(new OFstream(outputDir/fieldName));

	outputFilePtr() << "# Time Alpha" << endl;

	Info << "Starting calculation" << nl << endl;
	forAll(timeDirs, timeI)
	{
	

		Info << "Field: " << field << nl << endl;
		runTime.setTime(timeDirs[timeI], timeI);
		Info << "Time " << runTime.timeName() << " s" << nl << endl;

		// Create field based on argument
		#include "createFields.H"

		scalar totalVolume = 0;
		scalar totalField = 0;
	    for (label cellI = 0; cellI < mesh.C().size(); cellI++)
		{
	        if (cellI%20 == 0) // only show every twentieth cell not to spam the screen too much
			{
	            //Info << "Cell " << cellI << " with centre at " << mesh.C()[cellI] << " volume " << 						mesh.V()[cellI] << endl;
			}
			totalVolume += mesh.V()[cellI];
			totalField += alpha_liq[cellI]*mesh.V()[cellI];
		}

	    Info << "Volume: " << totalVolume << " Volume OF: " << gSum(mesh.V()) << endl;
    	Info << "Alpha: " << totalField/totalVolume << nl << endl;
		outputFilePtr() << runTime.timeName() << " " << totalField/totalVolume << endl;

	}
    Info<< "Finished!" << endl;

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
