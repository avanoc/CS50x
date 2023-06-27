import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, url_for, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.before_first_request
def init_app():
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    userId = session["user_id"]
    cash = float((db.execute("SELECT cash FROM users WHERE id = ?", userId))[0]['cash'])
    portfolio = db.execute("SELECT * FROM portfolio WHERE UserID = ?", userId)
    balance = cash
    for p in portfolio:
        balance = balance + p["total"]
    return render_template("index.html", cash=[cash], balance=[balance], portfolio=portfolio)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    elif request.method == "POST":
        # Check if symbol exists
        symbol = request.form.get("symbol").upper()
        quote = lookup(symbol)
        if quote == None:
            return apology("Please enter a valid symbol", 400)

        # Get price for desired symbol.
        price = quote['price']

        # Ensure the user has entered a valid amount of shares
        shares = request.form.get("shares")
        if str(shares).isnumeric() == False:
            return apology("Please enter a valid amount of shares", 400)
        shares = int(shares)

        # Ensure user has enough money to pay.
        paid = float(price) * shares
        userId = session["user_id"]
        cash = float((db.execute("SELECT cash FROM users WHERE id = ?", userId))[0]['cash'])
        today = datetime.now()
        if paid > cash:
            return apology("You can't buy that much!", 400)

        # Save transaction.
        else:
            db.execute("INSERT INTO stocks('symbol', 'numShares', 'priceBuy', 'date', 'UserID') VALUES(?, ?, ?, ?, ?)",
                       symbol, shares, price, today, userId)

            # Update cash available for user.
            cashLeft = cash - paid
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cashLeft, userId)

            # Check if symbol already exists in portfolio
            portfolio = db.execute("SELECT * FROM portfolio WHERE UserID = ?", userId)
            s = 0
            for i in portfolio:
                if symbol == i["symbol"]:
                    s = 1
                    db.execute("UPDATE portfolio SET numShares = ?, current = ?, total = ? WHERE symbol = ?",
                               i['numShares'] + shares, price, i['numShares'] * price + shares * price, symbol)

            # if symbol doesn't exist in portfolio
            if s == 0:
                db.execute("INSERT INTO portfolio('UserID', 'symbol', 'numShares', 'current', 'total') VALUES(?, ?, ?, ?, ?)",
                           userId, symbol, shares, price, shares * price)
            return redirect(url_for('index'))


@app.route("/history")
@login_required
def history():
    userId = session["user_id"]

    # display all stocks owned in 1 table:
    stocks = db.execute("SELECT * FROM stocks WHERE UserID = ? ORDER BY date DESC", userId)

    # Ensure there are transactions.
    if len(db.execute("SELECT * FROM stocks WHERE UserID = ?", userId)) == 0:
        return apology("You haven't made any transactions yet", 403)

    # Get transactions history.
    else:
        return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect(url_for('index'))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        # Ensure symbol exists.
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Please enter a valid stock symbol.", 400)

        # Return stock data.
        else:
            return render_template("quote.html", name=quote['name'], symbol=quote['symbol'].upper(), price=quote['price'], isQuote=True)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    else:
        # Ensure all fields are filled.
        if request.form.get("username") == "" or request.form.get("password") == "" or request.form.get("confirmation") == "":
            return apology("Please fill all the fields.", 400)

        # Ensure the selected password is well typed both in password and confirm password fields.
        elif request.form.get("password") == request.form.get("confirmation"):

            # Ensure username doesn't exist.
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            if len(rows) != 0:
                return apology("Username is already taken. Please choose a different username", 400)

            else:
                # Generate hash of the password.
                hash = generate_password_hash(request.form.get("password"))

                # Add new user to database.
                db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)",
                           request.form.get("username"), hash, "100000")

                # Query database for username
                rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

                # Remember which user has logged in
                session["user_id"] = rows[0]["id"]

                # Redirect user to home page
                return redirect(url_for('index'))

        else:
            return apology("Your password/confirm password fields do not match.", 400)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    userId = session["user_id"]
    if request.method == "GET":
        options = db.execute("SELECT symbol FROM portfolio WHERE UserID = ?", userId)
        return render_template("sell.html", options=options)

    elif request.method == "POST":
        # Get price for desired symbol.
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        price = float(quote['price'])

        # Ensure user has enough stocks to sell.
        shares = int(request.form.get("shares"))
        portfolio = db.execute("SELECT * FROM portfolio WHERE UserID = ?", userId)
        owned = 0
        for stock in portfolio:
            if symbol == stock["symbol"]:
                owned = stock["numShares"]
        if shares > owned:
            return apology("You don't have enough shares to sell", 400)

        else:
            # Save transaction.
            today = datetime.now()
            db.execute("INSERT INTO stocks('symbol', 'numShares', 'priceSell', 'date', 'UserID') VALUES(?, ?, ?, ?, ?)",
                       symbol, shares, -1 * price, today, userId)

            # Update balance.
            cash = float((db.execute("SELECT cash FROM users WHERE id = ?", userId))[0]['cash'])
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + price * shares, userId)

            # Update Portfolio.
            for stock in portfolio:
                if symbol == stock["symbol"]:
                    left = stock["numShares"] - shares
                    if left == 0:
                        db.execute("DELETE FROM portfolio WHERE symbol = ? AND UserID = ?", symbol, userId)
                    else:
                        db.execute("UPDATE portfolio SET numShares = ?, total = ? WHERE symbol = ? AND UserID = ?",
                                   left, left * price, symbol, userId)
            return redirect(url_for('index'))