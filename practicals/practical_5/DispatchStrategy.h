/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

DispatchStrategy.h (Strategy, Strategy)
*/

#ifndef DISPATCHSTRATEGY_H
#define DISPATCHSTRATEGY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Types.h"

class Incident;

class ResponseUnit;
class SecurityTeam;
class MedicalTeam;
class FacilitiesTeam;

class DispatchStrategy
{
	public:
		virtual ~DispatchStrategy() { };
		virtual vector<ResponseUnit*> selectUnits(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities) = 0;
		virtual string label() const = 0;
		/// <summary>
		/// high severity will return evacuate and low severity will return lockdown
		/// </summary>
		virtual AlertType alertMessage() const = 0;
};

class HighSeverity: public DispatchStrategy
{
	public:
		/// <summary>
		/// return { security, medical, facilities }
		/// when we report an incident, we will determine the strategy used based on the severity and print its label. for each unit in the vector, the report incident will issue a command, after building a dispatch unit out of it (see the relevant functions for more info)
		/// </summary>
		vector<ResponseUnit*> selectUnits(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities) override;
		/// <summary>
		/// return "High-severity: full response (Security + Medical + Facilities)"
		/// </summary>
		string label() const override;
		AlertType alertMessage() const override;
};

class LowSeverity: public DispatchStrategy
{
	public:
		/// <summary>
		/// return { security }
		/// </summary>
		vector<ResponseUnit*> selectUnits(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities) override;
		/// <summary>
		/// return "Low-severity: security-only response"
		/// </summary>
		string label() const override;
		AlertType alertMessage() const override;
};

#endif // DISPATCHSTRATEGY_H