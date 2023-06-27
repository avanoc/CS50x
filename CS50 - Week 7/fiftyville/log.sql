-- Keep a log of any SQL queries you execute as you solve the mystery.

-- QUERY: Check if there's a crime scene report on the date and place of the theft:
SELECT * FROM crime_scene_reports WHERE day = "28" AND month = "7" AND year = "2021" AND street LIKE "%Humphrey%";
-- RESULT: Crime ID: 295. 3 witneses all mentioned a bakery. Time of theft: 10.15 am

-- QUERY: Check interviews performed on the same day:
SELECT * FROM interviews WHERE day = "28" AND month = "7" AND year = "2021" AND transcript LIKE "%bakery%";
-- RESULT: 3 witneses (Ruth, Eugene and Raymond). A car left the parking lot around 10 minutes after the theft.
-- the thief was withdrawing money from ATM on Legget St. earlier that day. Thief said on the phone he would take first flight from next morning.

-- QUERY: Check bakery security logs between 10.15 and 10.25:
SELECT * FROM bakery_security_logs WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND minute BETWEEN "15" AND "25";
-- RESULT: 8 cars, all leaving the parking lot.

-- QUERY: Check ATM logs from :
SELECT * FROM atm_transactions WHERE day = "28" AND month = "7" AND year = "2021" AND atm_location LIKE "%LEGGET%";
-- RESULT: 9 transactions. 8 withdraws and 1 deposit.

-- QUERY: Find destination of first flight from Fiftyville on 7/29/21:
SELECT full_name, city
FROM airports
WHERE id =(
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id = (
        SELECT id
        FROM airports
        WHERE full_name
        lIKE "%fiftyville%"
        )
    AND day = "29"
    AND month = "7"
    AND year = "2021"
    ORDER BY hour, minute
    LIMIT 1
);
-- RESULT: La Guardia Airport, NYC.

-- QUERY: Find thief:
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = "28"
    AND month = "7"
    AND year = "2021"
    AND hour = "10"
    AND minute BETWEEN "15" AND "25"
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = "28"
    AND month = "7"
    AND year = "2021"
    AND duration <= "60"
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE origin_airport_id = (
            SELECT id
            FROM airports
            WHERE full_name LIKE "%fiftyville%"
        )
        AND destination_airport_id IN (
            SELECT id
            FROM airports
            WHERE full_name LIKE "%Guardia%"
        )
        AND day = "29"
        AND month = "7"
        AND year = "2021"
    )
)
AND id IN(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = "28"
        AND month = "7"
        AND year = "2021"
        AND atm_location LIKE "%LEGGET%"
    )
);
-- RESULT: Bruce.

-- QUERY: Find accomplice:
SELECT name
FROM people
WHERE phone_number IN(
    SELECT receiver
    FROM phone_calls
    WHERE day = "28"
    AND month = "7"
    AND year = "2021"
    AND duration <= "60"
    AND caller = (
        SELECT phone_number
        FROM people
        WHERE name = "Bruce"
    )
);
-- RESULT: Robin.