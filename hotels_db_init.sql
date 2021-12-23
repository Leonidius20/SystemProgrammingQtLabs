--
-- PostgreSQL database dump
--

-- Dumped from database version 14.1
-- Dumped by pg_dump version 14.1

-- Started on 2021-12-23 22:28:20

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 209 (class 1259 OID 16520)
-- Name: Hotels; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Hotels" (
    code integer NOT NULL,
    name text NOT NULL,
    country text NOT NULL,
    city text NOT NULL,
    address text NOT NULL,
    stars integer NOT NULL,
    contact_name text,
    contact_phone text
);


ALTER TABLE public."Hotels" OWNER TO postgres;

--
-- TOC entry 3304 (class 0 OID 16520)
-- Dependencies: 209
-- Data for Name: Hotels; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Hotels" (code, name, country, city, address, stars, contact_name, contact_phone) FROM stdin;
\.


--
-- TOC entry 3164 (class 2606 OID 16526)
-- Name: Hotels Hotels_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Hotels"
    ADD CONSTRAINT "Hotels_pkey" PRIMARY KEY (code);


-- Completed on 2021-12-23 22:28:20

--
-- PostgreSQL database dump complete
--

