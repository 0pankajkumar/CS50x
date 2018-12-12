import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    i = 0
    sumz = 0
    grand = []
    name = []
    symbol = db.execute("SELECT DISTINCT stock FROM history WHERE id=:idx", idx=session['user_id'])
    for values in symbol:
        details = []
        details.append(values['stock'])

        try:
            box = lookup(values['stock'])
        except:
            return apology("Lookup at IEX failed")

        details.append(box["name"])

        shares = db.execute("SELECT SUM(quantity) from history WHERE stock=:stock AND id=:idx",
                            stock=values['stock'], idx=session["user_id"])
        details.append(shares[0]['SUM(quantity)'])

        price = box["price"]
        details.append(price)

        total = usd(float(shares[0]['SUM(quantity)']) * float(price))
        details.append(total)

        grand.append(details)
        i = i + 1

        sumz += float(shares[0]['SUM(quantity)']) * float(price)

    cash = db.execute("SELECT cash FROM users WHERE id = :sess_id",
                              sess_id=session['user_id'])
    total = cash[0]['cash'] + sumz
    return render_template("index.html", grand=grand, cash=usd(cash[0]['cash']), total=usd(total))



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buyPage.html")
    elif request.method == "POST":

        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Invalid stock symbol")

        try:
            quantity = int(request.form.get("shares"))
        except ValueError:
            return apology("Not a number in Quantity", 400)

        if (not quantity or ((quantity % quantity) > 0) or (quantity < 0)):
            return apology("quantity should be a natural number", 400)
        balance1 = db.execute("SELECT cash FROM users WHERE id = :sess_id",
                              sess_id=session['user_id'])
        quantity = int(quantity)
        balance = float(balance1[0]['cash'])

        if not quote:
            return apology("Stockname error")
        elif not quantity:
            return apology("Quantity error")
        price = quote['price']

        total = float(price * quantity)

        if (total >= balance):
            return apology("Insufficient Cash")
        else:
            db.execute("INSERT INTO history (id,stock,price,quantity) VALUES (:id,:stockname,:price,:q)",
                       stockname=quote["symbol"], price=price, id=session['user_id'], q=quantity)
            db.execute("UPDATE users SET cash = cash - :total WHERE id = :id",
                       total=total, id=session['user_id'])
            return redirect('/')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    i = 0
    sumz = 0
    grand = []
    name = []
    symbol = db.execute("SELECT stock,price,quantity,time FROM history WHERE id=:idx", idx=session['user_id'])
    for values in symbol:
        details = []
        details.append(values['stock'])

        details.append(values["price"])

        details.append(values['quantity'])

        details.append(values['time'])

        grand.append(details)
        i = i + 1

    return render_template("history.html", grand=grand)


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
        return render_template("welcome.html")

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
    if request.method == "GET":
        return render_template("quotePage.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol == "":
            return apology("Please enter something yaar!")
        elif not symbol.isalpha():
            return apology("Only valid symbols please")
        try:
            quote = lookup(symbol)
        except:
            return apology("Lookup failed, Not my fault")

        if not quote:
            return apology("Invalid symbol yaar!")

        price = float(quote['price'])
        if not quote:
            return apology("Invalid stock symbol")
        else:
            return render_template("stockInfo.html", name=quote['name'], symbol=quote['symbol'], price=quote['price'])
    return apology("Aw, Snap!")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        rows2 = db.execute("SELECT username FROM users WHERE username = :u", u=request.form.get("username"))

        if rows2:
            return apology("Username exists already")

        hashiq = generate_password_hash(request.form.get("password"))

        # Query database for registration
        if (request.form.get("password") == request.form.get("confirmation")):
            rows = db.execute("INSERT INTO users(id,username,hash) VALUES(NULL,:username,:hashi)",
                              username=request.form.get("username"), hashi=hashiq)
        else:
            return apology("Passwords don't match")

        # Query database for automatic login after registerattion
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return render_template("welcome.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    idx = session['user_id']

    if request.method == "GET":
        stocks = db.execute("SELECT DISTINCT stock FROM history WHERE id=:id", id=session["user_id"])
        return render_template("sellPage.html", stocks=stocks)
    elif request.method == "POST":

        availabl = db.execute("SELECT SUM(quantity) FROM history WHERE stock=:stk AND id = :idx",
                              stk=request.form.get("symbol"), idx=idx)
        available = availabl[0]["SUM(quantity)"]
        try:
            quote = lookup(request.form.get("symbol"))
        except:
            return apology("Lookup failed")
        price = float(quote['price'])
        qty = float(request.form.get("shares"))
        amount = qty * price

        if available < float(request.form.get("shares")):
            return apology("Can't sell what you don't own")

        db.execute("INSERT INTO history (id,stock,price,quantity) VALUES (:idx,:stock,:price,:quantity)",
                   idx=idx, stock=quote["symbol"], price=price, quantity=-1*qty)
        db.execute("UPDATE users SET cash=cash+:amnt", amnt=amount)

        return redirect("/")

    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
