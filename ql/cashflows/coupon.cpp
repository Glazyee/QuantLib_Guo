/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2003, 2004, 2007 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/cashflows/coupon.hpp>
#include <ql/time/daycounter.hpp>

namespace QuantLib {

    Coupon::Coupon(Real nominal,
                   const Date& paymentDate,
                   const Date& accrualStartDate,
                   const Date& accrualEndDate,
                   const Date& refPeriodStart,
                   const Date& refPeriodEnd)
    : nominal_(nominal), paymentDate_(paymentDate),
      accrualStartDate_(accrualStartDate), accrualEndDate_(accrualEndDate),
      refPeriodStart_(refPeriodStart), refPeriodEnd_(refPeriodEnd) {
        if (refPeriodStart_ == Date())
            refPeriodStart_ = accrualStartDate_;
        if (refPeriodEnd_ == Date())
            refPeriodEnd_ = accrualEndDate_;
    }

    Time Coupon::accrualPeriod() const {
        return dayCounter().yearFraction(accrualStartDate_,
                                         accrualEndDate_,
                                         refPeriodStart_,
                                         refPeriodEnd_);
    }

    Integer Coupon::accrualDays() const {
        return dayCounter().dayCount(accrualStartDate_,
                                     accrualEndDate_);
    }

    void Coupon::accept(AcyclicVisitor& v) {
        Visitor<Coupon>* v1 = dynamic_cast<Visitor<Coupon>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            CashFlow::accept(v);
    }

}