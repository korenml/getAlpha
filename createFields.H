Info << "Reading field " << field << endl;
	volScalarField alpha_liq
	(
		IOobject
		(
			field,
			runTime.timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionedScalar("alpha_liq", dimensionSet(0,0,0,0,0,0,0), 0.0) 
	);
