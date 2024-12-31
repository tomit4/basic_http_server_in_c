# Basic HTTP Server In C

This repository contains the source code for a plain HTTP server written in C.
It is purely for educational purposes and does not implement the robust error
handling nor the feature set necessary for a modern HTTP server, but is meant to
demonstrate the basics of sockets, file streams, and the HTTP protocol for
educational purposes.

The majority of the source code originated from
[Jidar Ahmed Amin's Medium
Article on the subject](https://medium.com/@justup1080/tutorial-creating-a-minimalist-http-server-in-c-2303d140c725).
If you're reading this Jidar, thank you for your fantastic article on the
subject and solid starting reference point for this.

**TODO:**

- [ ] Read environment variables from a `.env` file so that things like PORT can
      be read and passed into the initial server constructor.
- [ ] Serve other static files so that we can style our html file, use some
      basic javascript, and serve up some images.
- [ ] Set it up to read multiple HTML files (i.e. /about, /blog, etc.).
- [ ] Set up server to be able to handle multiple concurrent users.
