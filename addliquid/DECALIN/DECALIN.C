/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

#include "DECALIN.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(DECALIN, 0);
    addToRunTimeSelectionTable(liquidProperties, DECALIN,);
    addToRunTimeSelectionTable(liquidProperties, DECALIN, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::DECALIN::DECALIN()
:
    liquidProperties
    (
        138,
        645,
        2.08e+6,
        0.48,
        0.247,
        243.51,
        1.393,
        464.4,
        0.0,
        0.4923,
        1.57e+4
    ),
    rho_(114.2, 0.3273, 645, 0.3037),
    pv_(112.73, -9749.6, -13.245, 7.1266e-06, 2.0),
    hl_(645.70, 464743.296904101, 0.39797, 0.0, 0.0, 0.0),
    Cp_
    (
        1958.18252099659,
       -1.39094071757388,
        0.00754612221948905,
        0.0,
        0.0,
        0.0
    ),
    h_
    (
       -2699436.15229142,
        1958.18252099659,
       -0.695470358786942,
        0.00251537407316302,
        0.0,
        0.0
    ),
    Cpg_(1175.10630073444, 3762.16748076045, 1614.1, 2658.04547211582, 742),
    B_
    (
        0.00337351091119935,
       -4.13606494008504,
       -534560.916470464,
       -1.13364022911762e+19,
        2.80704220402713e+21
    ),
    mu_(-16.53, 1974, 0.6791, 0.0, 0.0),
    mug_(2.64e-08, 0.9487, 71.0, 0.0),
    kappa_(0.2063, -0.000254, 0.0, 0.0, 0.0, 0.0),
    kappag_(-668.4, 0.9323, -4071000000.0, 0.0),
    sigma_(645, 0.06017, 1.049, 0.0, 0.0, 0.0),
    D_(147.18, 20.1, 142.285, 28.0) // note: Same as nHeptane
{}


Foam::DECALIN::DECALIN
(
    const liquidProperties& l,
    const NSRDSfunc5& density,
    const NSRDSfunc1& vapourPressure,
    const NSRDSfunc6& heatOfVapourisation,
    const NSRDSfunc0& heatCapacity,
    const NSRDSfunc0& enthalpy,
    const NSRDSfunc7& idealGasHeatCapacity,
    const NSRDSfunc4& secondVirialCoeff,
    const NSRDSfunc1& dynamicViscosity,
    const NSRDSfunc2& vapourDynamicViscosity,
    const NSRDSfunc0& thermalConductivity,
    const NSRDSfunc2& vapourThermalConductivity,
    const NSRDSfunc6& surfaceTension,
    const APIdiffCoefFunc& vapourDiffussivity
)
:
    liquidProperties(l),
    rho_(density),
    pv_(vapourPressure),
    hl_(heatOfVapourisation),
    Cp_(heatCapacity),
    h_(enthalpy),
    Cpg_(idealGasHeatCapacity),
    B_(secondVirialCoeff),
    mu_(dynamicViscosity),
    mug_(vapourDynamicViscosity),
    kappa_(thermalConductivity),
    kappag_(vapourThermalConductivity),
    sigma_(surfaceTension),
    D_(vapourDiffussivity)
{}


Foam::DECALIN::DECALIN(const dictionary& dict)
:
    DECALIN()
{
    readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::DECALIN::writeData(Ostream& os) const
{
    liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream& os, const DECALIN& l)
{
    l.writeData(os);
    return os;
}


// ************************************************************************* //
