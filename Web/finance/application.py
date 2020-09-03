import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    stocks = db.execute("SELECT * FROM stocks WHERE user_id=:user_id ORDER BY symbol ASC", user_id=user_id)
    rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=user_id)
    cash = rows[0]["cash"]

    totalprice = 0
    for i in range(len(stocks)):
        totalprice += stocks[i]["total"]

    totalprice += float(cash)
    return render_template("index.html", stocks=stocks, cash=cash, totalprice=totalprice)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        quote = lookup(symbol)
        shares = request.form.get("shares")
        user_id = session["user_id"]

        if not symbol or not shares:
            flash("missing data")
            return render_template("buy.html")

        if not quote:
            flash("Invalid Symbol")
            return render_template("buy.html")

        total_price = float(quote["price"]) * float(shares)

        rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=user_id)
        savings = float(rows[0]["cash"])

        if savings < total_price:
            return apology("There is not enough money")

        else:
            savings_left = savings - total_price

            # Checking if symbol is already owned
            stock = db.execute("SELECT * FROM stocks WHERE user_id=:user_id AND symbol=:symbol",
            user_id=user_id, symbol=quote["symbol"])

            # If its already owned, just update
            if len(stock) == 1:
                new_share = int(stock[0]["shares"]) + int(shares)
                new_total = float(stock[0]["total"]) + total_price

                # Updating the stocks table
                db.execute("UPDATE stocks SET shares=:shares, total=:total WHERE user_id=:user_id AND symbol=:symbol",
                shares=new_share, total=new_total, user_id=user_id, symbol=symbol)

            else:
               db.execute("INSERT INTO stocks (user_id, symbol, name, shares, pps, total) VALUES (:user_id, :symbol, :name, :shares, :pps, :total)",
               user_id=user_id, symbol=symbol, name=quote["name"], shares=shares, pps=quote["price"], total=total_price)

            # Updating the total chash in users table
            db.execute("UPDATE users SET cash =:cash WHERE id =:id", cash=savings_left, id=user_id)

            db.execute("INSERT INTO history (user_id, symbol, shares, pps) VALUES (:user_id, :symbol, :shares, :pps)",
            user_id=user_id, symbol=quote["symbol"], shares=shares, pps=quote["price"])

            flash("Bought!")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    history = db.execute("SELECT * FROM history WHERE user_id=:user_id ORDER BY symbol ASC", user_id=user_id)

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if not symbol:
            return apology("missing symbol")

        if not quote:
            return apology("invalid symbol")

        return render_template("quoted.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            flash("Must provide a username")
            return redirect("/register")


        # Ensure password was submitted
        elif not request.form.get("password"):
            flash("Must provide a password")
            return redirect("/register")

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("passwordconf"):
            flash("Password do not match")
            return redirect("/register")

        # Checking if username is taken
        check = db.execute("SELECT * FROM users WHERE username=:username", username=request.form.get("username"))
        if len(check) >= 1:
            flash("Username is taken")
            return redirect("/register")

        # Hashing password
        hash = generate_password_hash(request.form.get("password"))

         # Inserting new
        new_user = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=hash)

        # Remember which user has logged in
        session["user_id"] = new_user

        # Display a flash message
        flash("Registered!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol FROM stocks WHERE user_id=:user_id", user_id=user_id)

    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")


        stocks_db = db.execute("SELECT * FROM stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=user_id, symbol=symbol)

        # Ensure number of shares is available to be sold
        if int(shares) > stocks_db[0]["shares"]:
            flash("Not enough shares")
            return render_template("sell.html", stocks=stocks)

        quote = lookup(symbol)
        totalprice = float(quote["price"]) * float(shares)

        # Update stocks database
        updated_shares = int(stocks_db[0]["shares"]) - int(shares)

        if updated_shares == 0:
            db.execute("DELETE FROM stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=user_id, symbol=symbol)
        else:
            new_shares = int(stocks_db[0]["shares"]) - int(shares)
            new_total = float(new_shares) * float(stocks_db[0]["pps"])

            db.execute("UPDATE stocks SET shares=:shares, total=:total WHERE user_id=:user_id AND symbol=:symbol",
            shares=new_shares, total=new_total, user_id=user_id, symbol=symbol)

        # Update total cash
        user = db.execute("SELECT * FROM users WHERE id=:id", id=user_id)
        total_cash = float(user[0]["cash"]) + totalprice
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=total_cash, id=user_id)

        # Update history database
        db.execute("INSERT INTO history (user_id, symbol, shares, pps) VALUES (:user_id, :symbol, :shares, :pps)",
        user_id=user_id, symbol=quote["symbol"], shares=-int(shares), pps=quote["price"])

        flash("Sold!")
        return redirect("/")

    return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
